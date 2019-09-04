#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct greybus_descriptor_cport {int protocol_id; int /*<<< orphan*/  id; } ;
struct greybus_bundle_id {int dummy; } ;
struct gb_connection {TYPE_1__* intf; } ;
struct TYPE_4__ {int /*<<< orphan*/  release; int /*<<< orphan*/  interface_id; int /*<<< orphan*/ * ops; struct gb_camera* priv; } ;
struct gb_camera {struct gb_bundle* bundle; TYPE_2__ module; struct gb_connection* connection; scalar_t__ data_cport_id; int /*<<< orphan*/  state; int /*<<< orphan*/  mutex; } ;
struct gb_bundle {int num_cports; struct greybus_descriptor_cport* cport_desc; } ;
struct TYPE_3__ {int /*<<< orphan*/  interface_id; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GB_CAMERA_STATE_UNCONFIGURED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  GREYBUS_PROTOCOL_CAMERA_DATA 129 
#define  GREYBUS_PROTOCOL_CAMERA_MGMT 128 
 scalar_t__ IS_ERR (struct gb_connection*) ; 
 int PTR_ERR (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_cam_ops ; 
 int /*<<< orphan*/  gb_camera_cleanup (struct gb_camera*) ; 
 int gb_camera_debugfs_init (struct gb_camera*) ; 
 int gb_camera_register (TYPE_2__*) ; 
 int /*<<< orphan*/  gb_camera_release_module ; 
 int /*<<< orphan*/  gb_camera_request_handler ; 
 struct gb_connection* gb_connection_create (struct gb_bundle*,scalar_t__,int /*<<< orphan*/ ) ; 
 int gb_connection_enable (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connection_set_data (struct gb_connection*,struct gb_camera*) ; 
 int /*<<< orphan*/  gb_pm_runtime_put_autosuspend (struct gb_bundle*) ; 
 int /*<<< orphan*/  greybus_set_drvdata (struct gb_bundle*,struct gb_camera*) ; 
 int /*<<< orphan*/  kfree (struct gb_camera*) ; 
 struct gb_camera* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gb_camera_probe(struct gb_bundle *bundle,
			   const struct greybus_bundle_id *id)
{
	struct gb_connection *conn;
	struct gb_camera *gcam;
	u16 mgmt_cport_id = 0;
	u16 data_cport_id = 0;
	unsigned int i;
	int ret;

	/*
	 * The camera bundle must contain exactly two CPorts, one for the
	 * camera management protocol and one for the camera data protocol.
	 */
	if (bundle->num_cports != 2)
		return -ENODEV;

	for (i = 0; i < bundle->num_cports; ++i) {
		struct greybus_descriptor_cport *desc = &bundle->cport_desc[i];

		switch (desc->protocol_id) {
		case GREYBUS_PROTOCOL_CAMERA_MGMT:
			mgmt_cport_id = le16_to_cpu(desc->id);
			break;
		case GREYBUS_PROTOCOL_CAMERA_DATA:
			data_cport_id = le16_to_cpu(desc->id);
			break;
		default:
			return -ENODEV;
		}
	}

	if (!mgmt_cport_id || !data_cport_id)
		return -ENODEV;

	gcam = kzalloc(sizeof(*gcam), GFP_KERNEL);
	if (!gcam)
		return -ENOMEM;

	mutex_init(&gcam->mutex);

	gcam->bundle = bundle;
	gcam->state = GB_CAMERA_STATE_UNCONFIGURED;
	gcam->data_cport_id = data_cport_id;

	conn = gb_connection_create(bundle, mgmt_cport_id,
				    gb_camera_request_handler);
	if (IS_ERR(conn)) {
		ret = PTR_ERR(conn);
		goto error;
	}

	gcam->connection = conn;
	gb_connection_set_data(conn, gcam);

	ret = gb_connection_enable(conn);
	if (ret)
		goto error;

	ret = gb_camera_debugfs_init(gcam);
	if (ret < 0)
		goto error;

	gcam->module.priv = gcam;
	gcam->module.ops = &gb_cam_ops;
	gcam->module.interface_id = gcam->connection->intf->interface_id;
	gcam->module.release = gb_camera_release_module;
	ret = gb_camera_register(&gcam->module);
	if (ret < 0)
		goto error;

	greybus_set_drvdata(bundle, gcam);

	gb_pm_runtime_put_autosuspend(gcam->bundle);

	return 0;

error:
	gb_camera_cleanup(gcam);
	kfree(gcam);
	return ret;
}