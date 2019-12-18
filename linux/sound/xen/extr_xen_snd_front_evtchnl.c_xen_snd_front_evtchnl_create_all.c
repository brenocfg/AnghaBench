#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct xen_front_cfg_card {int num_pcm_instances; struct xen_front_cfg_pcm_instance* pcm_instances; } ;
struct xen_snd_front_info {int num_evt_pairs; TYPE_4__* evt_pairs; TYPE_1__* xb_dev; struct xen_front_cfg_card cfg; } ;
struct xen_snd_front_evtchnl_pair {int dummy; } ;
struct xen_front_cfg_pcm_instance {int num_streams_pb; int num_streams_cap; TYPE_3__* streams_cap; TYPE_2__* streams_pb; } ;
struct device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  evt; int /*<<< orphan*/  req; } ;
struct TYPE_7__ {int index; } ;
struct TYPE_6__ {int index; } ;
struct TYPE_5__ {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EVTCHNL_TYPE_EVT ; 
 int /*<<< orphan*/  EVTCHNL_TYPE_REQ ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int evtchnl_alloc (struct xen_snd_front_info*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_snd_front_evtchnl_free_all (struct xen_snd_front_info*) ; 

int xen_snd_front_evtchnl_create_all(struct xen_snd_front_info *front_info,
				     int num_streams)
{
	struct xen_front_cfg_card *cfg = &front_info->cfg;
	struct device *dev = &front_info->xb_dev->dev;
	int d, ret = 0;

	front_info->evt_pairs =
			kcalloc(num_streams,
				sizeof(struct xen_snd_front_evtchnl_pair),
				GFP_KERNEL);
	if (!front_info->evt_pairs)
		return -ENOMEM;

	/* Iterate over devices and their streams and create event channels. */
	for (d = 0; d < cfg->num_pcm_instances; d++) {
		struct xen_front_cfg_pcm_instance *pcm_instance;
		int s, index;

		pcm_instance = &cfg->pcm_instances[d];

		for (s = 0; s < pcm_instance->num_streams_pb; s++) {
			index = pcm_instance->streams_pb[s].index;

			ret = evtchnl_alloc(front_info, index,
					    &front_info->evt_pairs[index].req,
					    EVTCHNL_TYPE_REQ);
			if (ret < 0) {
				dev_err(dev, "Error allocating control channel\n");
				goto fail;
			}

			ret = evtchnl_alloc(front_info, index,
					    &front_info->evt_pairs[index].evt,
					    EVTCHNL_TYPE_EVT);
			if (ret < 0) {
				dev_err(dev, "Error allocating in-event channel\n");
				goto fail;
			}
		}

		for (s = 0; s < pcm_instance->num_streams_cap; s++) {
			index = pcm_instance->streams_cap[s].index;

			ret = evtchnl_alloc(front_info, index,
					    &front_info->evt_pairs[index].req,
					    EVTCHNL_TYPE_REQ);
			if (ret < 0) {
				dev_err(dev, "Error allocating control channel\n");
				goto fail;
			}

			ret = evtchnl_alloc(front_info, index,
					    &front_info->evt_pairs[index].evt,
					    EVTCHNL_TYPE_EVT);
			if (ret < 0) {
				dev_err(dev, "Error allocating in-event channel\n");
				goto fail;
			}
		}
	}

	front_info->num_evt_pairs = num_streams;
	return 0;

fail:
	xen_snd_front_evtchnl_free_all(front_info);
	return ret;
}