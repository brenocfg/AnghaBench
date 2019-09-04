#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  maxpacket; } ;
struct TYPE_22__ {TYPE_2__ dwc_ep; } ;
struct TYPE_27__ {scalar_t__ setup_pkt_dma_handle; TYPE_3__ ep0; } ;
typedef  TYPE_8__ dwc_otg_pcd_t ;
struct TYPE_28__ {int setup_desc_index; TYPE_7__** out_ep_regs; scalar_t__* dma_setup_desc_addr; TYPE_10__** setup_desc_addr; } ;
typedef  TYPE_9__ dwc_otg_dev_if_t ;
struct TYPE_23__ {int l; int ioc; int /*<<< orphan*/  bs; scalar_t__ sts; int /*<<< orphan*/  bytes; scalar_t__ mtrf; scalar_t__ sr; } ;
struct TYPE_24__ {TYPE_4__ b; } ;
struct TYPE_16__ {TYPE_5__ status; scalar_t__ buf; } ;
typedef  TYPE_10__ dwc_otg_dev_dma_desc_t ;
struct TYPE_17__ {scalar_t__ snpsid; int /*<<< orphan*/  dma_desc_enable; scalar_t__ dma_enable; TYPE_9__* dev_if; } ;
typedef  TYPE_11__ dwc_otg_core_if_t ;
struct TYPE_20__ {int supcnt; int pktcnt; int xfersize; } ;
struct TYPE_18__ {scalar_t__ d32; TYPE_1__ b; } ;
typedef  TYPE_12__ deptsiz0_data_t ;
struct TYPE_25__ {int epena; int cnak; } ;
struct TYPE_19__ {scalar_t__ d32; TYPE_6__ b; } ;
typedef  TYPE_13__ depctl_data_t ;
struct TYPE_26__ {int /*<<< orphan*/  doepctl; int /*<<< orphan*/  doeptsiz; int /*<<< orphan*/  doepdma; } ;

/* Variables and functions */
 int /*<<< orphan*/  BS_HOST_BUSY ; 
 int /*<<< orphan*/  BS_HOST_READY ; 
 int /*<<< orphan*/  DWC_MODIFY_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ OTG_CORE_REV_2_94a ; 
 scalar_t__ OTG_CORE_REV_3_00a ; 

__attribute__((used)) static inline void ep0_out_start(dwc_otg_core_if_t * core_if,
				 dwc_otg_pcd_t * pcd)
{
	dwc_otg_dev_if_t *dev_if = core_if->dev_if;
	deptsiz0_data_t doeptsize0 = {.d32 = 0 };
	dwc_otg_dev_dma_desc_t *dma_desc;
	depctl_data_t doepctl = {.d32 = 0 };

#ifdef VERBOSE
	DWC_DEBUGPL(DBG_PCDV, "%s() doepctl0=%0x\n", __func__,
		    DWC_READ_REG32(&dev_if->out_ep_regs[0]->doepctl));
#endif
	if (core_if->snpsid >= OTG_CORE_REV_3_00a) {
		doepctl.d32 = DWC_READ_REG32(&dev_if->out_ep_regs[0]->doepctl);
		if (doepctl.b.epena) {
			return;
		}
	}

	doeptsize0.b.supcnt = 3;
	doeptsize0.b.pktcnt = 1;
	doeptsize0.b.xfersize = 8 * 3;

	if (core_if->dma_enable) {
		if (!core_if->dma_desc_enable) {
			/** put here as for Hermes mode deptisz register should not be written */
			DWC_WRITE_REG32(&dev_if->out_ep_regs[0]->doeptsiz,
					doeptsize0.d32);

			/** @todo dma needs to handle multiple setup packets (up to 3) */
			DWC_WRITE_REG32(&dev_if->out_ep_regs[0]->doepdma,
					pcd->setup_pkt_dma_handle);
		} else {
			dev_if->setup_desc_index =
			    (dev_if->setup_desc_index + 1) & 1;
			dma_desc =
			    dev_if->setup_desc_addr[dev_if->setup_desc_index];

			/** DMA Descriptor Setup */
			dma_desc->status.b.bs = BS_HOST_BUSY;
			if (core_if->snpsid >= OTG_CORE_REV_3_00a) {
				dma_desc->status.b.sr = 0;
				dma_desc->status.b.mtrf = 0;
			}
			dma_desc->status.b.l = 1;
			dma_desc->status.b.ioc = 1;
			dma_desc->status.b.bytes = pcd->ep0.dwc_ep.maxpacket;
			dma_desc->buf = pcd->setup_pkt_dma_handle;
			dma_desc->status.b.sts = 0;
			dma_desc->status.b.bs = BS_HOST_READY;

			/** DOEPDMA0 Register write */
			DWC_WRITE_REG32(&dev_if->out_ep_regs[0]->doepdma,
					dev_if->dma_setup_desc_addr
					[dev_if->setup_desc_index]);
		}

	} else {
		/** put here as for Hermes mode deptisz register should not be written */
		DWC_WRITE_REG32(&dev_if->out_ep_regs[0]->doeptsiz,
				doeptsize0.d32);
	}

	/** DOEPCTL0 Register write cnak will be set after setup interrupt */
	doepctl.d32 = 0;
	doepctl.b.epena = 1;
	if (core_if->snpsid <= OTG_CORE_REV_2_94a) {
	doepctl.b.cnak = 1;
	DWC_WRITE_REG32(&dev_if->out_ep_regs[0]->doepctl, doepctl.d32);
	} else {
		DWC_MODIFY_REG32(&dev_if->out_ep_regs[0]->doepctl, 0, doepctl.d32);
	}

#ifdef VERBOSE
	DWC_DEBUGPL(DBG_PCDV, "doepctl0=%0x\n",
		    DWC_READ_REG32(&dev_if->out_ep_regs[0]->doepctl));
	DWC_DEBUGPL(DBG_PCDV, "diepctl0=%0x\n",
		    DWC_READ_REG32(&dev_if->in_ep_regs[0]->diepctl));
#endif
}