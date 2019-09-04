#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct gb_camera_stream_config_response {int /*<<< orphan*/  max_size; int /*<<< orphan*/ * data_type; int /*<<< orphan*/  virtual_channel; void* format; void* height; void* width; scalar_t__ padding; } ;
struct gb_camera_stream_config_request {int /*<<< orphan*/  max_size; int /*<<< orphan*/ * data_type; int /*<<< orphan*/  virtual_channel; void* format; void* height; void* width; scalar_t__ padding; } ;
struct gb_camera_stream_config {int /*<<< orphan*/  max_size; int /*<<< orphan*/ * dt; int /*<<< orphan*/  vc; void* format; void* height; void* width; } ;
struct gb_camera_csi_params {int dummy; } ;
struct gb_camera_configure_streams_response {unsigned int num_streams; unsigned int flags; struct gb_camera_stream_config_response* config; scalar_t__ padding; } ;
struct gb_camera_configure_streams_request {unsigned int num_streams; unsigned int flags; struct gb_camera_stream_config_response* config; scalar_t__ padding; } ;
struct gb_camera {scalar_t__ state; int /*<<< orphan*/  mutex; int /*<<< orphan*/  bundle; int /*<<< orphan*/  connection; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int GB_CAMERA_CONFIGURE_STREAMS_ADJUSTED ; 
 int GB_CAMERA_CONFIGURE_STREAMS_TEST_ONLY ; 
 unsigned int GB_CAMERA_MAX_STREAMS ; 
 scalar_t__ GB_CAMERA_STATE_CONFIGURED ; 
 scalar_t__ GB_CAMERA_STATE_UNCONFIGURED ; 
 int /*<<< orphan*/  GB_CAMERA_TYPE_CONFIGURE_STREAMS ; 
 int /*<<< orphan*/  GB_OPERATION_FLAG_SHORT_RESPONSE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* cpu_to_le16 (void*) ; 
 int gb_camera_configure_streams_validate_response (struct gb_camera*,struct gb_camera_configure_streams_response*,unsigned int) ; 
 int gb_camera_operation_sync_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gb_camera_configure_streams_response*,size_t,struct gb_camera_configure_streams_response*,size_t*) ; 
 int gb_camera_setup_data_connection (struct gb_camera*,struct gb_camera_configure_streams_response*,struct gb_camera_csi_params*) ; 
 int /*<<< orphan*/  gb_camera_teardown_data_connection (struct gb_camera*) ; 
 int /*<<< orphan*/  gb_operation_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gb_camera_configure_streams_response*,int,struct gb_camera_configure_streams_response*,int) ; 
 int /*<<< orphan*/  gb_pm_runtime_get_noresume (int /*<<< orphan*/ ) ; 
 int gb_pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct gb_camera_configure_streams_response*) ; 
 struct gb_camera_configure_streams_response* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (void*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct gb_camera_configure_streams_response*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gb_camera_configure_streams(struct gb_camera *gcam,
				       unsigned int *num_streams,
				       unsigned int *flags,
				       struct gb_camera_stream_config *streams,
				       struct gb_camera_csi_params *csi_params)
{
	struct gb_camera_configure_streams_request *req;
	struct gb_camera_configure_streams_response *resp;
	unsigned int nstreams = *num_streams;
	unsigned int i;
	size_t req_size;
	size_t resp_size;
	int ret;

	if (nstreams > GB_CAMERA_MAX_STREAMS)
		return -EINVAL;

	req_size = sizeof(*req) + nstreams * sizeof(req->config[0]);
	resp_size = sizeof(*resp) + nstreams * sizeof(resp->config[0]);

	req = kmalloc(req_size, GFP_KERNEL);
	resp = kmalloc(resp_size, GFP_KERNEL);
	if (!req || !resp) {
		kfree(req);
		kfree(resp);
		return -ENOMEM;
	}

	req->num_streams = nstreams;
	req->flags = *flags;
	req->padding = 0;

	for (i = 0; i < nstreams; ++i) {
		struct gb_camera_stream_config_request *cfg = &req->config[i];

		cfg->width = cpu_to_le16(streams[i].width);
		cfg->height = cpu_to_le16(streams[i].height);
		cfg->format = cpu_to_le16(streams[i].format);
		cfg->padding = 0;
	}

	mutex_lock(&gcam->mutex);

	ret = gb_pm_runtime_get_sync(gcam->bundle);
	if (ret)
		goto done_skip_pm_put;

	if (!gcam->connection) {
		ret = -EINVAL;
		goto done;
	}

	ret = gb_camera_operation_sync_flags(gcam->connection,
					     GB_CAMERA_TYPE_CONFIGURE_STREAMS,
					     GB_OPERATION_FLAG_SHORT_RESPONSE,
					     req, req_size,
					     resp, &resp_size);
	if (ret < 0)
		goto done;

	ret = gb_camera_configure_streams_validate_response(gcam, resp,
							    nstreams);
	if (ret < 0)
		goto done;

	*flags = resp->flags;
	*num_streams = resp->num_streams;

	for (i = 0; i < resp->num_streams; ++i) {
		struct gb_camera_stream_config_response *cfg = &resp->config[i];

		streams[i].width = le16_to_cpu(cfg->width);
		streams[i].height = le16_to_cpu(cfg->height);
		streams[i].format = le16_to_cpu(cfg->format);
		streams[i].vc = cfg->virtual_channel;
		streams[i].dt[0] = cfg->data_type[0];
		streams[i].dt[1] = cfg->data_type[1];
		streams[i].max_size = le32_to_cpu(cfg->max_size);
	}

	if ((resp->flags & GB_CAMERA_CONFIGURE_STREAMS_ADJUSTED) ||
	    (req->flags & GB_CAMERA_CONFIGURE_STREAMS_TEST_ONLY))
		goto done;

	if (gcam->state == GB_CAMERA_STATE_CONFIGURED) {
		gb_camera_teardown_data_connection(gcam);
		gcam->state = GB_CAMERA_STATE_UNCONFIGURED;

		/*
		 * When unconfiguring streams release the PM runtime reference
		 * that was acquired when streams were configured. The bundle
		 * won't be suspended until the PM runtime reference acquired at
		 * the beginning of this function gets released right before
		 * returning.
		 */
		gb_pm_runtime_put_noidle(gcam->bundle);
	}

	if (resp->num_streams == 0)
		goto done;

	/*
	 * Make sure the bundle won't be suspended until streams get
	 * unconfigured after the stream is configured successfully
	 */
	gb_pm_runtime_get_noresume(gcam->bundle);

	/* Setup CSI-2 connection from APB-A to AP */
	ret = gb_camera_setup_data_connection(gcam, resp, csi_params);
	if (ret < 0) {
		memset(req, 0, sizeof(*req));
		gb_operation_sync(gcam->connection,
				  GB_CAMERA_TYPE_CONFIGURE_STREAMS,
				  req, sizeof(*req),
				  resp, sizeof(*resp));
		*flags = 0;
		*num_streams = 0;
		gb_pm_runtime_put_noidle(gcam->bundle);
		goto done;
	}

	gcam->state = GB_CAMERA_STATE_CONFIGURED;

done:
	gb_pm_runtime_put_autosuspend(gcam->bundle);

done_skip_pm_put:
	mutex_unlock(&gcam->mutex);
	kfree(req);
	kfree(resp);
	return ret;
}