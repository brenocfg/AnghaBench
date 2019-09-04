#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_9__ ;
typedef  struct TYPE_39__   TYPE_8__ ;
typedef  struct TYPE_38__   TYPE_7__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_20__ ;
typedef  struct TYPE_31__   TYPE_1__ ;
typedef  struct TYPE_30__   TYPE_18__ ;
typedef  struct TYPE_29__   TYPE_17__ ;
typedef  struct TYPE_28__   TYPE_16__ ;
typedef  struct TYPE_27__   TYPE_15__ ;
typedef  struct TYPE_26__   TYPE_14__ ;
typedef  struct TYPE_25__   TYPE_13__ ;
typedef  struct TYPE_24__   TYPE_12__ ;
typedef  struct TYPE_23__   TYPE_11__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int int32_t ;
struct TYPE_40__ {int goutnakeff; } ;
struct TYPE_23__ {char* d32; TYPE_9__ b; } ;
typedef  TYPE_11__ gintsts_data_t ;
struct TYPE_31__ {int goutnakeff; } ;
struct TYPE_24__ {int /*<<< orphan*/  d32; TYPE_1__ b; } ;
typedef  TYPE_12__ gintmsk_data_t ;
struct TYPE_25__ {TYPE_4__* core_if; } ;
typedef  TYPE_13__ dwc_otg_pcd_t ;
struct TYPE_26__ {int num_out_eps; TYPE_8__** out_ep_regs; int /*<<< orphan*/ * isoc_ep; TYPE_6__* dev_global_regs; } ;
typedef  TYPE_14__ dwc_otg_dev_if_t ;
struct TYPE_27__ {size_t num; } ;
typedef  TYPE_15__ dwc_ep_t ;
struct TYPE_28__ {void* d32; } ;
typedef  TYPE_16__ doepint_data_t ;
struct TYPE_38__ {int epdis; int snak; scalar_t__ epena; } ;
struct TYPE_29__ {char* d32; TYPE_7__ b; } ;
typedef  TYPE_17__ depctl_data_t ;
struct TYPE_36__ {int cgoutnak; } ;
struct TYPE_30__ {char* d32; TYPE_5__ b; } ;
typedef  TYPE_18__ dctl_data_t ;
struct TYPE_39__ {int /*<<< orphan*/  doepctl; int /*<<< orphan*/  doepint; } ;
struct TYPE_37__ {int /*<<< orphan*/  dctl; } ;
struct TYPE_35__ {TYPE_3__* ep_xfer_info; TYPE_2__* core_params; } ;
struct TYPE_34__ {int state; } ;
struct TYPE_33__ {scalar_t__ dev_out_nak; } ;
struct TYPE_32__ {TYPE_10__* core_global_regs; TYPE_14__* dev_if; } ;
struct TYPE_22__ {int /*<<< orphan*/  gintsts; int /*<<< orphan*/  gintmsk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_MODIFY_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_PRINTF (char*,char*) ; 
 void* DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,char*) ; 
 TYPE_20__* GET_CORE_IF (TYPE_13__*) ; 

int32_t dwc_otg_pcd_handle_out_nak_effective(dwc_otg_pcd_t * pcd)
{
	dwc_otg_dev_if_t *dev_if = GET_CORE_IF(pcd)->dev_if;
	gintmsk_data_t intr_mask = {.d32 = 0 };
	gintsts_data_t gintsts;
	depctl_data_t doepctl;
	int i;

	/* Disable the Global OUT NAK Effective Interrupt */
	intr_mask.b.goutnakeff = 1;
	DWC_MODIFY_REG32(&GET_CORE_IF(pcd)->core_global_regs->gintmsk,
		intr_mask.d32, 0);

	/* If DEV OUT NAK enabled*/
	if (pcd->core_if->core_params->dev_out_nak) {
		/* Run over all out endpoints to determine the ep number on
		 * which the timeout has happened
		 */
		for (i = 0; i <= dev_if->num_out_eps; i++) {
			if ( pcd->core_if->ep_xfer_info[i].state == 2 )
				break;
		}
		if (i > dev_if->num_out_eps) {
			dctl_data_t dctl;
			dctl.d32 =
			    DWC_READ_REG32(&dev_if->dev_global_regs->dctl);
			dctl.b.cgoutnak = 1;
			DWC_WRITE_REG32(&dev_if->dev_global_regs->dctl,
				dctl.d32);
			goto out;
		}

		/* Disable the endpoint */
		doepctl.d32 = DWC_READ_REG32(&dev_if->out_ep_regs[i]->doepctl);
		if (doepctl.b.epena) {
			doepctl.b.epdis = 1;
			doepctl.b.snak = 1;
		}
		DWC_WRITE_REG32(&dev_if->out_ep_regs[i]->doepctl, doepctl.d32);
		return 1;
	}
	/* We come here from Incomplete ISO OUT handler */
	if (dev_if->isoc_ep) {
		dwc_ep_t *dwc_ep = (dwc_ep_t *)dev_if->isoc_ep;
		uint32_t epnum = dwc_ep->num;
		doepint_data_t doepint;
		doepint.d32 =
		    DWC_READ_REG32(&dev_if->out_ep_regs[dwc_ep->num]->doepint);
		dev_if->isoc_ep = NULL;
		doepctl.d32 =
		    DWC_READ_REG32(&dev_if->out_ep_regs[epnum]->doepctl);
		DWC_PRINTF("Before disable DOEPCTL = %08x\n", doepctl.d32);
		if (doepctl.b.epena) {
			doepctl.b.epdis = 1;
			doepctl.b.snak = 1;
		}
		DWC_WRITE_REG32(&dev_if->out_ep_regs[epnum]->doepctl,
				doepctl.d32);
		return 1;
	} else
		DWC_PRINTF("INTERRUPT Handler not implemented for %s\n",
			   "Global OUT NAK Effective\n");

out:
	/* Clear interrupt */
	gintsts.d32 = 0;
	gintsts.b.goutnakeff = 1;
	DWC_WRITE_REG32(&GET_CORE_IF(pcd)->core_global_regs->gintsts,
			gintsts.d32);

	return 1;
}