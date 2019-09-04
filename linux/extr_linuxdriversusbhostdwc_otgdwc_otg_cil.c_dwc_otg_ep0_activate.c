#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_24__ {TYPE_6__* dev_global_regs; TYPE_4__** out_ep_regs; TYPE_2__** in_ep_regs; } ;
typedef  TYPE_7__ dwc_otg_dev_if_t ;
struct TYPE_25__ {scalar_t__ snpsid; TYPE_7__* dev_if; } ;
typedef  TYPE_8__ dwc_otg_core_if_t ;
struct TYPE_26__ {scalar_t__ stp_rollover; } ;
typedef  TYPE_9__ dwc_ep_t ;
struct TYPE_18__ {int enumspd; } ;
struct TYPE_15__ {TYPE_1__ b; void* d32; } ;
typedef  TYPE_10__ dsts_data_t ;
struct TYPE_20__ {int epena; int /*<<< orphan*/  mps; } ;
struct TYPE_16__ {void* d32; TYPE_3__ b; } ;
typedef  TYPE_11__ depctl_data_t ;
struct TYPE_22__ {int cgnpinnak; } ;
struct TYPE_17__ {int /*<<< orphan*/  d32; TYPE_5__ b; } ;
typedef  TYPE_12__ dctl_data_t ;
struct TYPE_23__ {int /*<<< orphan*/  dctl; int /*<<< orphan*/  dsts; } ;
struct TYPE_21__ {int /*<<< orphan*/  doepctl; } ;
struct TYPE_19__ {int /*<<< orphan*/  diepctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PCDV ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  DWC_DEP0CTL_MPS_64 ; 
 int /*<<< orphan*/  DWC_DEP0CTL_MPS_8 ; 
#define  DWC_DSTS_ENUMSPD_FS_PHY_30MHZ_OR_60MHZ 131 
#define  DWC_DSTS_ENUMSPD_FS_PHY_48MHZ 130 
#define  DWC_DSTS_ENUMSPD_HS_PHY_30MHZ_OR_60MHZ 129 
#define  DWC_DSTS_ENUMSPD_LS_PHY_6MHZ 128 
 int /*<<< orphan*/  DWC_MODIFY_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,void*) ; 
 scalar_t__ OTG_CORE_REV_2_94a ; 

void dwc_otg_ep0_activate(dwc_otg_core_if_t * core_if, dwc_ep_t * ep)
{
	dwc_otg_dev_if_t *dev_if = core_if->dev_if;
	dsts_data_t dsts;
	depctl_data_t diepctl;
	depctl_data_t doepctl;
	dctl_data_t dctl = {.d32 = 0 };

	ep->stp_rollover = 0;
	/* Read the Device Status and Endpoint 0 Control registers */
	dsts.d32 = DWC_READ_REG32(&dev_if->dev_global_regs->dsts);
	diepctl.d32 = DWC_READ_REG32(&dev_if->in_ep_regs[0]->diepctl);
	doepctl.d32 = DWC_READ_REG32(&dev_if->out_ep_regs[0]->doepctl);

	/* Set the MPS of the IN EP based on the enumeration speed */
	switch (dsts.b.enumspd) {
	case DWC_DSTS_ENUMSPD_HS_PHY_30MHZ_OR_60MHZ:
	case DWC_DSTS_ENUMSPD_FS_PHY_30MHZ_OR_60MHZ:
	case DWC_DSTS_ENUMSPD_FS_PHY_48MHZ:
		diepctl.b.mps = DWC_DEP0CTL_MPS_64;
		break;
	case DWC_DSTS_ENUMSPD_LS_PHY_6MHZ:
		diepctl.b.mps = DWC_DEP0CTL_MPS_8;
		break;
	}

	DWC_WRITE_REG32(&dev_if->in_ep_regs[0]->diepctl, diepctl.d32);

	/* Enable OUT EP for receive */
	if (core_if->snpsid <= OTG_CORE_REV_2_94a) {
	doepctl.b.epena = 1;
	DWC_WRITE_REG32(&dev_if->out_ep_regs[0]->doepctl, doepctl.d32);
	}
#ifdef VERBOSE
	DWC_DEBUGPL(DBG_PCDV, "doepctl0=%0x\n",
		    DWC_READ_REG32(&dev_if->out_ep_regs[0]->doepctl));
	DWC_DEBUGPL(DBG_PCDV, "diepctl0=%0x\n",
		    DWC_READ_REG32(&dev_if->in_ep_regs[0]->diepctl));
#endif
	dctl.b.cgnpinnak = 1;

	DWC_MODIFY_REG32(&dev_if->dev_global_regs->dctl, dctl.d32, dctl.d32);
	DWC_DEBUGPL(DBG_PCDV, "dctl=%0x\n",
		    DWC_READ_REG32(&dev_if->dev_global_regs->dctl));

}