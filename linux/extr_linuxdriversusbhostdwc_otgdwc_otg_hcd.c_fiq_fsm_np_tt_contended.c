#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int devaddr; int epnum; } ;
struct TYPE_15__ {TYPE_4__ b; } ;
struct fiq_channel_state {int fsm; TYPE_5__ hcchar_copy; } ;
struct TYPE_17__ {TYPE_6__* channel; } ;
typedef  TYPE_7__ dwc_otg_qh_t ;
struct TYPE_18__ {TYPE_3__* fiq_state; TYPE_2__* core_if; } ;
typedef  TYPE_8__ dwc_otg_hcd_t ;
struct TYPE_16__ {int dev_addr; int ep_num; int hc_num; } ;
struct TYPE_13__ {struct fiq_channel_state* channel; } ;
struct TYPE_12__ {TYPE_1__* core_params; } ;
struct TYPE_11__ {int host_channels; } ;

/* Variables and functions */
#define  FIQ_NP_IN_CSPLIT_RETRY 132 
#define  FIQ_NP_OUT_CSPLIT_RETRY 131 
#define  FIQ_NP_SSPLIT_PENDING 130 
#define  FIQ_NP_SSPLIT_RETRY 129 
#define  FIQ_NP_SSPLIT_STARTED 128 

int fiq_fsm_np_tt_contended(dwc_otg_hcd_t *hcd, dwc_otg_qh_t *qh)
{
	int i;
	struct fiq_channel_state *st;
	int dev_addr = qh->channel->dev_addr;
	int ep_num = qh->channel->ep_num;
	for (i = 0; i < hcd->core_if->core_params->host_channels; i++) {
		if (i == qh->channel->hc_num)
			continue;
		st = &hcd->fiq_state->channel[i];
		switch (st->fsm) {
		case FIQ_NP_SSPLIT_STARTED:
		case FIQ_NP_SSPLIT_RETRY:
		case FIQ_NP_SSPLIT_PENDING:
		case FIQ_NP_OUT_CSPLIT_RETRY:
		case FIQ_NP_IN_CSPLIT_RETRY:
			if (st->hcchar_copy.b.devaddr == dev_addr &&
				st->hcchar_copy.b.epnum == ep_num)
				return 1;
			break;
		default:
			break;
		}
	}
	return 0;
}