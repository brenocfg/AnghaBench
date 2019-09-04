#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_12__ {int nptxfempty; int ginnakeff; } ;
struct TYPE_16__ {int /*<<< orphan*/  d32; TYPE_1__ b; } ;
typedef  TYPE_5__ gintmsk_data_t ;
typedef  int /*<<< orphan*/  dwc_otg_pcd_t ;
struct TYPE_17__ {int stopped; } ;
typedef  TYPE_6__ dwc_otg_pcd_ep_t ;
struct TYPE_18__ {TYPE_4__* dev_global_regs; } ;
typedef  TYPE_7__ dwc_otg_dev_if_t ;
struct TYPE_19__ {TYPE_2__* core_global_regs; int /*<<< orphan*/  dma_enable; TYPE_7__* dev_if; } ;
typedef  TYPE_8__ dwc_otg_core_if_t ;
struct TYPE_14__ {int sgnpinnak; } ;
struct TYPE_20__ {int /*<<< orphan*/  d32; TYPE_3__ b; } ;
typedef  TYPE_9__ dctl_data_t ;
struct TYPE_15__ {int /*<<< orphan*/  dctl; } ;
struct TYPE_13__ {int /*<<< orphan*/  gintmsk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_MODIFY_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_8__* GET_CORE_IF (int /*<<< orphan*/ *) ; 
 TYPE_6__* get_in_ep (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 

__attribute__((used)) static inline void handle_in_ep_timeout_intr(dwc_otg_pcd_t * pcd,
					     const uint32_t epnum)
{
	dwc_otg_core_if_t *core_if = GET_CORE_IF(pcd);
	dwc_otg_dev_if_t *dev_if = core_if->dev_if;

#ifdef DEBUG
	deptsiz_data_t dieptsiz = {.d32 = 0 };
	uint32_t num = 0;
#endif
	dctl_data_t dctl = {.d32 = 0 };
	dwc_otg_pcd_ep_t *ep;

	gintmsk_data_t intr_mask = {.d32 = 0 };

	ep = get_in_ep(pcd, epnum);

	/* Disable the NP Tx Fifo Empty Interrrupt */
	if (!core_if->dma_enable) {
		intr_mask.b.nptxfempty = 1;
		DWC_MODIFY_REG32(&core_if->core_global_regs->gintmsk,
				 intr_mask.d32, 0);
	}
	/** @todo NGS Check EP type.
	 * Implement for Periodic EPs */
	/*
	 * Non-periodic EP
	 */
	/* Enable the Global IN NAK Effective Interrupt */
	intr_mask.b.ginnakeff = 1;
	DWC_MODIFY_REG32(&core_if->core_global_regs->gintmsk, 0, intr_mask.d32);

	/* Set Global IN NAK */
	dctl.b.sgnpinnak = 1;
	DWC_MODIFY_REG32(&dev_if->dev_global_regs->dctl, dctl.d32, dctl.d32);

	ep->stopped = 1;

#ifdef DEBUG
	dieptsiz.d32 = DWC_READ_REG32(&dev_if->in_ep_regs[num]->dieptsiz);
	DWC_DEBUGPL(DBG_ANY, "pktcnt=%d size=%d\n",
		    dieptsiz.b.pktcnt, dieptsiz.b.xfersize);
#endif

#ifdef DISABLE_PERIODIC_EP
	/*
	 * Set the NAK bit for this EP to
	 * start the disable process.
	 */
	diepctl.d32 = 0;
	diepctl.b.snak = 1;
	DWC_MODIFY_REG32(&dev_if->in_ep_regs[num]->diepctl, diepctl.d32,
			 diepctl.d32);
	ep->disabling = 1;
	ep->stopped = 1;
#endif
}