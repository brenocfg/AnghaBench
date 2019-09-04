#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_15__ ;
typedef  struct TYPE_25__   TYPE_13__ ;
typedef  struct TYPE_24__   TYPE_12__ ;
typedef  struct TYPE_23__   TYPE_11__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int int32_t ;
struct TYPE_33__ {int usbtrdtim; int ulpi_utmi_sel; } ;
struct TYPE_35__ {scalar_t__ d32; TYPE_7__ b; } ;
typedef  TYPE_9__ gusbcfg_data_t ;
struct TYPE_34__ {int enumdone; } ;
struct TYPE_22__ {scalar_t__ d32; TYPE_8__ b; } ;
typedef  TYPE_10__ gintsts_data_t ;
struct TYPE_24__ {scalar_t__ stopped; int /*<<< orphan*/  dwc_ep; } ;
struct TYPE_23__ {scalar_t__ ep0state; TYPE_1__* fops; TYPE_12__ ep0; } ;
typedef  TYPE_11__ dwc_otg_pcd_t ;
typedef  TYPE_12__ dwc_otg_pcd_ep_t ;
struct TYPE_25__ {int /*<<< orphan*/  gintsts; int /*<<< orphan*/  gusbcfg; } ;
typedef  TYPE_13__ dwc_otg_core_global_regs_t ;
struct TYPE_32__ {int phy_utmi_width; } ;
struct TYPE_30__ {scalar_t__ hs_phy_type; } ;
struct TYPE_31__ {TYPE_4__ b; } ;
struct TYPE_28__ {int utmi_phy_data_width; } ;
struct TYPE_29__ {TYPE_2__ b; } ;
struct TYPE_27__ {int /*<<< orphan*/  (* connect ) (TYPE_11__*,int) ;} ;
struct TYPE_26__ {scalar_t__ snpsid; TYPE_13__* core_global_regs; TYPE_6__* core_params; TYPE_5__ hwcfg2; TYPE_3__ hwcfg4; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PCD ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ DWC_HWCFG2_HS_PHY_TYPE_ULPI ; 
 scalar_t__ DWC_HWCFG2_HS_PHY_TYPE_UTMI ; 
 scalar_t__ DWC_HWCFG2_HS_PHY_TYPE_UTMI_ULPI ; 
 scalar_t__ DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ EP0_DISCONNECT ; 
 void* EP0_IDLE ; 
 scalar_t__ EP0_STALL ; 
 TYPE_15__* GET_CORE_IF (TYPE_11__*) ; 
 scalar_t__ OTG_CORE_REV_2_60a ; 
 scalar_t__ OTG_CORE_REV_3_00a ; 
 int USB_SPEED_HIGH ; 
 int /*<<< orphan*/  dwc_otg_ep0_activate (TYPE_15__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ep0_out_start (TYPE_15__*,TYPE_11__*) ; 
 int get_device_speed (TYPE_15__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_11__*,int) ; 

int32_t dwc_otg_pcd_handle_enum_done_intr(dwc_otg_pcd_t * pcd)
{
	dwc_otg_pcd_ep_t *ep0 = &pcd->ep0;
	gintsts_data_t gintsts;
	gusbcfg_data_t gusbcfg;
	dwc_otg_core_global_regs_t *global_regs =
	    GET_CORE_IF(pcd)->core_global_regs;
	uint8_t utmi16b, utmi8b;
	int speed;
	DWC_DEBUGPL(DBG_PCD, "SPEED ENUM\n");

	if (GET_CORE_IF(pcd)->snpsid >= OTG_CORE_REV_2_60a) {
		utmi16b = 6;	//vahrama old value was 6;
		utmi8b = 9;
	} else {
		utmi16b = 4;
		utmi8b = 8;
	}
	dwc_otg_ep0_activate(GET_CORE_IF(pcd), &ep0->dwc_ep);
	if (GET_CORE_IF(pcd)->snpsid >= OTG_CORE_REV_3_00a) {
		ep0_out_start(GET_CORE_IF(pcd), pcd);
	}

#ifdef DEBUG_EP0
	print_ep0_state(pcd);
#endif

	if (pcd->ep0state == EP0_DISCONNECT) {
		pcd->ep0state = EP0_IDLE;
	} else if (pcd->ep0state == EP0_STALL) {
		pcd->ep0state = EP0_IDLE;
	}

	pcd->ep0state = EP0_IDLE;

	ep0->stopped = 0;

	speed = get_device_speed(GET_CORE_IF(pcd));
	pcd->fops->connect(pcd, speed);

	/* Set USB turnaround time based on device speed and PHY interface. */
	gusbcfg.d32 = DWC_READ_REG32(&global_regs->gusbcfg);
	if (speed == USB_SPEED_HIGH) {
		if (GET_CORE_IF(pcd)->hwcfg2.b.hs_phy_type ==
		    DWC_HWCFG2_HS_PHY_TYPE_ULPI) {
			/* ULPI interface */
			gusbcfg.b.usbtrdtim = 9;
		}
		if (GET_CORE_IF(pcd)->hwcfg2.b.hs_phy_type ==
		    DWC_HWCFG2_HS_PHY_TYPE_UTMI) {
			/* UTMI+ interface */
			if (GET_CORE_IF(pcd)->hwcfg4.b.utmi_phy_data_width == 0) {
				gusbcfg.b.usbtrdtim = utmi8b;
			} else if (GET_CORE_IF(pcd)->hwcfg4.
				   b.utmi_phy_data_width == 1) {
				gusbcfg.b.usbtrdtim = utmi16b;
			} else if (GET_CORE_IF(pcd)->
				   core_params->phy_utmi_width == 8) {
				gusbcfg.b.usbtrdtim = utmi8b;
			} else {
				gusbcfg.b.usbtrdtim = utmi16b;
			}
		}
		if (GET_CORE_IF(pcd)->hwcfg2.b.hs_phy_type ==
		    DWC_HWCFG2_HS_PHY_TYPE_UTMI_ULPI) {
			/* UTMI+  OR  ULPI interface */
			if (gusbcfg.b.ulpi_utmi_sel == 1) {
				/* ULPI interface */
				gusbcfg.b.usbtrdtim = 9;
			} else {
				/* UTMI+ interface */
				if (GET_CORE_IF(pcd)->
				    core_params->phy_utmi_width == 16) {
					gusbcfg.b.usbtrdtim = utmi16b;
				} else {
					gusbcfg.b.usbtrdtim = utmi8b;
				}
			}
		}
	} else {
		/* Full or low speed */
		gusbcfg.b.usbtrdtim = 9;
	}
	DWC_WRITE_REG32(&global_regs->gusbcfg, gusbcfg.d32);

	/* Clear interrupt */
	gintsts.d32 = 0;
	gintsts.b.enumdone = 1;
	DWC_WRITE_REG32(&GET_CORE_IF(pcd)->core_global_regs->gintsts,
			gintsts.d32);
	return 1;
}