#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_9__ ;
typedef  struct TYPE_35__   TYPE_8__ ;
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;
typedef  struct TYPE_27__   TYPE_19__ ;
typedef  struct TYPE_26__   TYPE_16__ ;
typedef  struct TYPE_25__   TYPE_15__ ;
typedef  struct TYPE_24__   TYPE_14__ ;
typedef  struct TYPE_23__   TYPE_13__ ;
typedef  struct TYPE_22__   TYPE_12__ ;
typedef  struct TYPE_21__   TYPE_11__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_34__ {int prtena; int prtconndet; int prtenchng; int prtovrcurrchng; scalar_t__ prtspd; } ;
struct TYPE_36__ {void* d32; TYPE_7__ b; } ;
typedef  TYPE_9__ hprt0_data_t ;
struct TYPE_31__ {int /*<<< orphan*/  frint; } ;
struct TYPE_20__ {void* d32; TYPE_4__ b; } ;
typedef  TYPE_10__ hfir_data_t ;
struct TYPE_35__ {scalar_t__ fslspclksel; } ;
struct TYPE_21__ {void* d32; TYPE_8__ b; } ;
typedef  TYPE_11__ hcfg_data_t ;
struct TYPE_32__ {int phylpwrclksel; } ;
struct TYPE_22__ {void* d32; TYPE_5__ b; } ;
typedef  TYPE_12__ gusbcfg_data_t ;
struct TYPE_23__ {int /*<<< orphan*/ * hprt0; TYPE_6__* host_global_regs; } ;
typedef  TYPE_13__ dwc_otg_host_if_t ;
struct TYPE_29__ {int port_connect_status_change; int port_connect_status; scalar_t__ port_speed; int port_reset_change; int port_enable_change; int port_over_current_change; } ;
struct TYPE_30__ {TYPE_2__ b; } ;
struct TYPE_24__ {TYPE_19__* core_if; TYPE_3__ flags; int /*<<< orphan*/  reset_tasklet; int /*<<< orphan*/  conn_timer; } ;
typedef  TYPE_14__ dwc_otg_hcd_t ;
struct TYPE_25__ {scalar_t__ host_ls_low_power_phy_clk; scalar_t__ host_support_fs_ls_low_power; } ;
typedef  TYPE_15__ dwc_otg_core_params_t ;
struct TYPE_26__ {int /*<<< orphan*/  gusbcfg; } ;
typedef  TYPE_16__ dwc_otg_core_global_regs_t ;
struct TYPE_33__ {int /*<<< orphan*/  hcfg; int /*<<< orphan*/  hfir; } ;
struct TYPE_28__ {int vbuson_timer_started; int /*<<< orphan*/  vbuson_timer; } ;
struct TYPE_27__ {int hibernation_suspend; TYPE_13__* host_if; TYPE_16__* core_global_regs; TYPE_15__* core_params; TYPE_1__ adp; scalar_t__ adp_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_CIL ; 
 int /*<<< orphan*/  DBG_HCD ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ DWC_HCFG_48_MHZ ; 
 scalar_t__ DWC_HCFG_6_MHZ ; 
 scalar_t__ DWC_HOST_LS_LOW_POWER_PHY_CLK_PARAM_6MHZ ; 
 scalar_t__ DWC_HPRT0_PRTSPD_FULL_SPEED ; 
 scalar_t__ DWC_HPRT0_PRTSPD_LOW_SPEED ; 
 int /*<<< orphan*/  DWC_PRINTF (char*) ; 
 void* DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_TASK_SCHEDULE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_TIMER_CANCEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  calc_frame_interval (TYPE_19__*) ; 
 int /*<<< orphan*/  init_hcd_usecs (TYPE_14__*) ; 
 scalar_t__ microframe_schedule ; 

int32_t dwc_otg_hcd_handle_port_intr(dwc_otg_hcd_t * dwc_otg_hcd)
{
	int retval = 0;
	hprt0_data_t hprt0;
	hprt0_data_t hprt0_modify;

	hprt0.d32 = DWC_READ_REG32(dwc_otg_hcd->core_if->host_if->hprt0);
	hprt0_modify.d32 = DWC_READ_REG32(dwc_otg_hcd->core_if->host_if->hprt0);

	/* Clear appropriate bits in HPRT0 to clear the interrupt bit in
	 * GINTSTS */

	hprt0_modify.b.prtena = 0;
	hprt0_modify.b.prtconndet = 0;
	hprt0_modify.b.prtenchng = 0;
	hprt0_modify.b.prtovrcurrchng = 0;

	/* Port Connect Detected
	 * Set flag and clear if detected */
	if (dwc_otg_hcd->core_if->hibernation_suspend == 1) {
		// Dont modify port status if we are in hibernation state
		hprt0_modify.b.prtconndet = 1;
		hprt0_modify.b.prtenchng = 1;
		DWC_WRITE_REG32(dwc_otg_hcd->core_if->host_if->hprt0, hprt0_modify.d32);
		hprt0.d32 = DWC_READ_REG32(dwc_otg_hcd->core_if->host_if->hprt0);
		return retval;
	}

	if (hprt0.b.prtconndet) {
		/** @todo - check if steps performed in 'else' block should be perfromed regardles adp */
		if (dwc_otg_hcd->core_if->adp_enable &&
				dwc_otg_hcd->core_if->adp.vbuson_timer_started == 1) {
			DWC_PRINTF("PORT CONNECT DETECTED ----------------\n");
			DWC_TIMER_CANCEL(dwc_otg_hcd->core_if->adp.vbuson_timer);
			dwc_otg_hcd->core_if->adp.vbuson_timer_started = 0;
			/* TODO - check if this is required, as
			 * host initialization was already performed
			 * after initial ADP probing
			 */
			/*dwc_otg_hcd->core_if->adp.vbuson_timer_started = 0;
			dwc_otg_core_init(dwc_otg_hcd->core_if);
			dwc_otg_enable_global_interrupts(dwc_otg_hcd->core_if);
			cil_hcd_start(dwc_otg_hcd->core_if);*/
		} else {

			DWC_DEBUGPL(DBG_HCD, "--Port Interrupt HPRT0=0x%08x "
				    "Port Connect Detected--\n", hprt0.d32);
			dwc_otg_hcd->flags.b.port_connect_status_change = 1;
			dwc_otg_hcd->flags.b.port_connect_status = 1;
			hprt0_modify.b.prtconndet = 1;

			/* B-Device has connected, Delete the connection timer. */
			DWC_TIMER_CANCEL(dwc_otg_hcd->conn_timer);
		}
		/* The Hub driver asserts a reset when it sees port connect
		 * status change flag */
		retval |= 1;
	}

	/* Port Enable Changed
	 * Clear if detected - Set internal flag if disabled */
	if (hprt0.b.prtenchng) {
		DWC_DEBUGPL(DBG_HCD, "  --Port Interrupt HPRT0=0x%08x "
			    "Port Enable Changed--\n", hprt0.d32);
		hprt0_modify.b.prtenchng = 1;
		if (hprt0.b.prtena == 1) {
			hfir_data_t hfir;
			int do_reset = 0;
			dwc_otg_core_params_t *params =
			    dwc_otg_hcd->core_if->core_params;
			dwc_otg_core_global_regs_t *global_regs =
			    dwc_otg_hcd->core_if->core_global_regs;
			dwc_otg_host_if_t *host_if =
			    dwc_otg_hcd->core_if->host_if;

			dwc_otg_hcd->flags.b.port_speed = hprt0.b.prtspd;
			if (microframe_schedule)
				init_hcd_usecs(dwc_otg_hcd);

			/* Every time when port enables calculate
			 * HFIR.FrInterval
			 */
			hfir.d32 = DWC_READ_REG32(&host_if->host_global_regs->hfir);
			hfir.b.frint = calc_frame_interval(dwc_otg_hcd->core_if);
			DWC_WRITE_REG32(&host_if->host_global_regs->hfir, hfir.d32);

			/* Check if we need to adjust the PHY clock speed for
			 * low power and adjust it */
			if (params->host_support_fs_ls_low_power) {
				gusbcfg_data_t usbcfg;

				usbcfg.d32 =
				    DWC_READ_REG32(&global_regs->gusbcfg);

				if (hprt0.b.prtspd == DWC_HPRT0_PRTSPD_LOW_SPEED
				    || hprt0.b.prtspd ==
				    DWC_HPRT0_PRTSPD_FULL_SPEED) {
					/*
					 * Low power
					 */
					hcfg_data_t hcfg;
					if (usbcfg.b.phylpwrclksel == 0) {
						/* Set PHY low power clock select for FS/LS devices */
						usbcfg.b.phylpwrclksel = 1;
						DWC_WRITE_REG32
						    (&global_regs->gusbcfg,
						     usbcfg.d32);
						do_reset = 1;
					}

					hcfg.d32 =
					    DWC_READ_REG32
					    (&host_if->host_global_regs->hcfg);

					if (hprt0.b.prtspd ==
					    DWC_HPRT0_PRTSPD_LOW_SPEED
					    && params->host_ls_low_power_phy_clk
					    ==
					    DWC_HOST_LS_LOW_POWER_PHY_CLK_PARAM_6MHZ)
					{
						/* 6 MHZ */
						DWC_DEBUGPL(DBG_CIL,
							    "FS_PHY programming HCFG to 6 MHz (Low Power)\n");
						if (hcfg.b.fslspclksel !=
						    DWC_HCFG_6_MHZ) {
							hcfg.b.fslspclksel =
							    DWC_HCFG_6_MHZ;
							DWC_WRITE_REG32
							    (&host_if->host_global_regs->hcfg,
							     hcfg.d32);
							do_reset = 1;
						}
					} else {
						/* 48 MHZ */
						DWC_DEBUGPL(DBG_CIL,
							    "FS_PHY programming HCFG to 48 MHz ()\n");
						if (hcfg.b.fslspclksel !=
						    DWC_HCFG_48_MHZ) {
							hcfg.b.fslspclksel =
							    DWC_HCFG_48_MHZ;
							DWC_WRITE_REG32
							    (&host_if->host_global_regs->hcfg,
							     hcfg.d32);
							do_reset = 1;
						}
					}
				} else {
					/*
					 * Not low power
					 */
					if (usbcfg.b.phylpwrclksel == 1) {
						usbcfg.b.phylpwrclksel = 0;
						DWC_WRITE_REG32
						    (&global_regs->gusbcfg,
						     usbcfg.d32);
						do_reset = 1;
					}
				}

				if (do_reset) {
					DWC_TASK_SCHEDULE(dwc_otg_hcd->reset_tasklet);
				}
			}

			if (!do_reset) {
				/* Port has been enabled set the reset change flag */
				dwc_otg_hcd->flags.b.port_reset_change = 1;
			}
		} else {
			dwc_otg_hcd->flags.b.port_enable_change = 1;
		}
		retval |= 1;
	}

	/** Overcurrent Change Interrupt */
	if (hprt0.b.prtovrcurrchng) {
		DWC_DEBUGPL(DBG_HCD, "  --Port Interrupt HPRT0=0x%08x "
			    "Port Overcurrent Changed--\n", hprt0.d32);
		dwc_otg_hcd->flags.b.port_over_current_change = 1;
		hprt0_modify.b.prtovrcurrchng = 1;
		retval |= 1;
	}

	/* Clear Port Interrupts */
	DWC_WRITE_REG32(dwc_otg_hcd->core_if->host_if->hprt0, hprt0_modify.d32);

	return retval;
}