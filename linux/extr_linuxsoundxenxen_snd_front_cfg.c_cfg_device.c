#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xen_snd_front_info {TYPE_1__* xb_dev; } ;
struct xen_front_cfg_stream {int dummy; } ;
struct xen_front_cfg_pcm_instance {int device_id; void* streams_cap; scalar_t__ num_streams_cap; void* streams_pb; scalar_t__ num_streams_pb; int /*<<< orphan*/  pcm_hw; int /*<<< orphan*/  name; } ;
struct snd_pcm_hardware {int dummy; } ;
typedef  int /*<<< orphan*/  node ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (char*) ; 
 int VSND_MAX_STREAM ; 
 int /*<<< orphan*/  XBT_NIL ; 
 int /*<<< orphan*/  XENSND_FIELD_DEVICE_NAME ; 
 int cfg_get_stream_type (char*,int,int*,int*) ; 
 int /*<<< orphan*/  cfg_read_pcm_hw (char*,struct snd_pcm_hardware*,int /*<<< orphan*/ *) ; 
 int cfg_stream (struct xen_snd_front_info*,struct xen_front_cfg_pcm_instance*,char*,int,int*,int*,int*) ; 
 void* devm_kcalloc (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ ) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,char const*,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  xenbus_exists (int /*<<< orphan*/ ,char*,char*) ; 
 char* xenbus_read (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cfg_device(struct xen_snd_front_info *front_info,
		      struct xen_front_cfg_pcm_instance *pcm_instance,
		      struct snd_pcm_hardware *parent_pcm_hw,
		      const char *path, int node_index, int *stream_cnt)
{
	char *str;
	char *device_path;
	int ret, i, num_streams;
	int num_pb, num_cap;
	int cur_pb, cur_cap;
	char node[3];

	device_path = kasprintf(GFP_KERNEL, "%s/%d", path, node_index);
	if (!device_path)
		return -ENOMEM;

	str = xenbus_read(XBT_NIL, device_path, XENSND_FIELD_DEVICE_NAME, NULL);
	if (!IS_ERR(str)) {
		strlcpy(pcm_instance->name, str, sizeof(pcm_instance->name));
		kfree(str);
	}

	pcm_instance->device_id = node_index;

	/*
	 * Check XenStore if PCM HW configuration exists for this device
	 * and update if so, e.g. we inherit all values from card's PCM HW,
	 * but can still override some of the values for the device.
	 */
	cfg_read_pcm_hw(device_path, parent_pcm_hw, &pcm_instance->pcm_hw);

	/* Find out how many streams were configured in Xen store. */
	num_streams = 0;
	do {
		snprintf(node, sizeof(node), "%d", num_streams);
		if (!xenbus_exists(XBT_NIL, device_path, node))
			break;

		num_streams++;
	} while (num_streams < VSND_MAX_STREAM);

	pcm_instance->num_streams_pb = 0;
	pcm_instance->num_streams_cap = 0;
	/* Get number of playback and capture streams. */
	for (i = 0; i < num_streams; i++) {
		ret = cfg_get_stream_type(device_path, i, &num_pb, &num_cap);
		if (ret < 0)
			goto fail;

		pcm_instance->num_streams_pb += num_pb;
		pcm_instance->num_streams_cap += num_cap;
	}

	if (pcm_instance->num_streams_pb) {
		pcm_instance->streams_pb =
				devm_kcalloc(&front_info->xb_dev->dev,
					     pcm_instance->num_streams_pb,
					     sizeof(struct xen_front_cfg_stream),
					     GFP_KERNEL);
		if (!pcm_instance->streams_pb) {
			ret = -ENOMEM;
			goto fail;
		}
	}

	if (pcm_instance->num_streams_cap) {
		pcm_instance->streams_cap =
				devm_kcalloc(&front_info->xb_dev->dev,
					     pcm_instance->num_streams_cap,
					     sizeof(struct xen_front_cfg_stream),
					     GFP_KERNEL);
		if (!pcm_instance->streams_cap) {
			ret = -ENOMEM;
			goto fail;
		}
	}

	cur_pb = 0;
	cur_cap = 0;
	for (i = 0; i < num_streams; i++) {
		ret = cfg_stream(front_info, pcm_instance, device_path, i,
				 &cur_pb, &cur_cap, stream_cnt);
		if (ret < 0)
			goto fail;
	}
	ret = 0;

fail:
	kfree(device_path);
	return ret;
}