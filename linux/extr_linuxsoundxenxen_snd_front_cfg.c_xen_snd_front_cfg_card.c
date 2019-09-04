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
struct xenbus_device {int /*<<< orphan*/  nodename; int /*<<< orphan*/  dev; } ;
struct xen_front_cfg_card {int num_pcm_instances; int /*<<< orphan*/  pcm_hw; int /*<<< orphan*/ * pcm_instances; } ;
struct xen_snd_front_info {struct xenbus_device* xb_dev; struct xen_front_cfg_card cfg; } ;
struct xen_front_cfg_pcm_instance {int dummy; } ;
typedef  int /*<<< orphan*/  node ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SNDRV_PCM_DEVICES ; 
 int /*<<< orphan*/  XBT_NIL ; 
 int cfg_device (struct xen_snd_front_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  cfg_read_pcm_hw (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  xenbus_exists (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

int xen_snd_front_cfg_card(struct xen_snd_front_info *front_info,
			   int *stream_cnt)
{
	struct xenbus_device *xb_dev = front_info->xb_dev;
	struct xen_front_cfg_card *cfg = &front_info->cfg;
	int ret, num_devices, i;
	char node[3];

	*stream_cnt = 0;
	num_devices = 0;
	do {
		snprintf(node, sizeof(node), "%d", num_devices);
		if (!xenbus_exists(XBT_NIL, xb_dev->nodename, node))
			break;

		num_devices++;
	} while (num_devices < SNDRV_PCM_DEVICES);

	if (!num_devices) {
		dev_warn(&xb_dev->dev,
			 "No devices configured for sound card at %s\n",
			 xb_dev->nodename);
		return -ENODEV;
	}

	/* Start from default PCM HW configuration for the card. */
	cfg_read_pcm_hw(xb_dev->nodename, NULL, &cfg->pcm_hw);

	cfg->pcm_instances =
			devm_kcalloc(&front_info->xb_dev->dev, num_devices,
				     sizeof(struct xen_front_cfg_pcm_instance),
				     GFP_KERNEL);
	if (!cfg->pcm_instances)
		return -ENOMEM;

	for (i = 0; i < num_devices; i++) {
		ret = cfg_device(front_info, &cfg->pcm_instances[i],
				 &cfg->pcm_hw, xb_dev->nodename, i, stream_cnt);
		if (ret < 0)
			return ret;
	}
	cfg->num_pcm_instances = num_devices;
	return 0;
}