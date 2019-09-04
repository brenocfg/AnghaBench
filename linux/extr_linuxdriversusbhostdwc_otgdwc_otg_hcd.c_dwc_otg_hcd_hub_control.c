#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_48__   TYPE_9__ ;
typedef  struct TYPE_47__   TYPE_8__ ;
typedef  struct TYPE_46__   TYPE_7__ ;
typedef  struct TYPE_45__   TYPE_6__ ;
typedef  struct TYPE_44__   TYPE_5__ ;
typedef  struct TYPE_43__   TYPE_4__ ;
typedef  struct TYPE_42__   TYPE_3__ ;
typedef  struct TYPE_41__   TYPE_2__ ;
typedef  struct TYPE_40__   TYPE_1__ ;
typedef  struct TYPE_39__   TYPE_19__ ;
typedef  struct TYPE_38__   TYPE_18__ ;
typedef  struct TYPE_37__   TYPE_17__ ;
typedef  struct TYPE_36__   TYPE_16__ ;
typedef  struct TYPE_35__   TYPE_15__ ;
typedef  struct TYPE_34__   TYPE_14__ ;
typedef  struct TYPE_33__   TYPE_13__ ;
typedef  struct TYPE_32__   TYPE_12__ ;
typedef  struct TYPE_31__   TYPE_11__ ;
typedef  struct TYPE_30__   TYPE_10__ ;

/* Type definitions */
struct TYPE_32__ {int bDescLength; int bDescriptorType; int bNbrPorts; int bPwrOn2PwrGood; int* DeviceRemovable; int /*<<< orphan*/  bHubContrCurrent; int /*<<< orphan*/  wHubCharacteristics; } ;
typedef  TYPE_12__ usb_hub_descriptor_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_48__ {int stoppclk; int enbl_sleep_gating; } ;
struct TYPE_33__ {int /*<<< orphan*/  d32; TYPE_9__ b; } ;
typedef  TYPE_13__ pcgcctl_data_t ;
struct TYPE_30__ {int prtena; int prtres; int prtsusp; int prtpwr; int prtrst; int /*<<< orphan*/  prttstctl; int /*<<< orphan*/  prtspd; int /*<<< orphan*/  prtovrcurract; int /*<<< orphan*/  prtconnsts; } ;
struct TYPE_34__ {void* d32; TYPE_10__ b; } ;
typedef  TYPE_14__ hprt0_data_t ;
struct TYPE_42__ {int ulpi_utmi_sel; } ;
struct TYPE_35__ {TYPE_3__ b; void* d32; } ;
typedef  TYPE_15__ gusbcfg_data_t ;
struct TYPE_43__ {int pmuactv; int pmuintsel; int disconn_det_msk; int lnstchng_msk; int sts_chngint_msk; int pwrdnclmp; int pwrdnswtch; } ;
struct TYPE_36__ {int /*<<< orphan*/  d32; TYPE_4__ b; } ;
typedef  TYPE_16__ gpwrdn_data_t ;
struct TYPE_45__ {int hstsethnpen; } ;
struct TYPE_37__ {int /*<<< orphan*/  d32; TYPE_6__ b; } ;
typedef  TYPE_17__ gotgctl_data_t ;
struct TYPE_40__ {int /*<<< orphan*/  port_connect_status; int /*<<< orphan*/  port_over_current_change; int /*<<< orphan*/  port_reset_change; int /*<<< orphan*/  port_l1_change; int /*<<< orphan*/  port_suspend_change; int /*<<< orphan*/  port_enable_change; int /*<<< orphan*/  port_connect_status_change; } ;
struct TYPE_41__ {TYPE_1__ b; int /*<<< orphan*/  d32; } ;
struct TYPE_38__ {TYPE_8__* fops; int /*<<< orphan*/  lock; TYPE_2__ flags; TYPE_19__* core_if; } ;
typedef  TYPE_18__ dwc_otg_hcd_t ;
struct TYPE_39__ {int power_down; int hibernation_suspend; void* lx_state; TYPE_11__* host_if; int /*<<< orphan*/ * pcgcctl; int /*<<< orphan*/  op_state; TYPE_7__* core_global_regs; TYPE_5__* gr_backup; } ;
typedef  TYPE_19__ dwc_otg_core_if_t ;
typedef  int /*<<< orphan*/  dwc_irqflags_t ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_47__ {int /*<<< orphan*/  (* get_b_hnp_enable ) (TYPE_18__*) ;} ;
struct TYPE_46__ {int /*<<< orphan*/  gotgctl; int /*<<< orphan*/  gpwrdn; int /*<<< orphan*/  gusbcfg; } ;
struct TYPE_44__ {void* gpwrdn_local; } ;
struct TYPE_31__ {int /*<<< orphan*/ * hprt0; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_SUSPEND ; 
 int /*<<< orphan*/  DBG_ANY ; 
 int /*<<< orphan*/  DBG_HCD ; 
 int /*<<< orphan*/  DBG_HCDV ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  DWC_ERROR (char*,int) ; 
 int DWC_E_INVALID ; 
 int /*<<< orphan*/  DWC_HPRT0_PRTSPD_HIGH_SPEED ; 
 int /*<<< orphan*/  DWC_HPRT0_PRTSPD_LOW_SPEED ; 
 int /*<<< orphan*/  DWC_MEMSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DWC_MODIFY_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* DWC_OTG_L0 ; 
 void* DWC_OTG_L2 ; 
 int /*<<< orphan*/  DWC_PRINTF (char*,...) ; 
 void* DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_SPINLOCK_IRQSAVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_SPINUNLOCK_IRQRESTORE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_WARN (char*,...) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,void*) ; 
#define  UCR_CLEAR_HUB_FEATURE 146 
#define  UCR_CLEAR_PORT_FEATURE 145 
#define  UCR_GET_HUB_DESCRIPTOR 144 
#define  UCR_GET_HUB_STATUS 143 
#define  UCR_GET_PORT_STATUS 142 
#define  UCR_SET_HUB_FEATURE 141 
#define  UCR_SET_PORT_FEATURE 140 
#define  UHF_C_HUB_LOCAL_POWER 139 
#define  UHF_C_HUB_OVER_CURRENT 138 
#define  UHF_C_PORT_CONNECTION 137 
#define  UHF_C_PORT_ENABLE 136 
 int UHF_C_PORT_L1 ; 
#define  UHF_C_PORT_OVER_CURRENT 135 
#define  UHF_C_PORT_RESET 134 
#define  UHF_C_PORT_SUSPEND 133 
 int UHF_PORT_CONNECTION ; 
#define  UHF_PORT_ENABLE 132 
 int UHF_PORT_HIGH_SPEED ; 
#define  UHF_PORT_INDICATOR 131 
 int UHF_PORT_L1 ; 
 int UHF_PORT_LOW_SPEED ; 
 int UHF_PORT_OVER_CURRENT ; 
#define  UHF_PORT_POWER 130 
#define  UHF_PORT_RESET 129 
#define  UHF_PORT_SUSPEND 128 
 int UHF_PORT_TEST ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dwc_cpu_to_le32 (int*) ; 
 int /*<<< orphan*/  dwc_mdelay (int) ; 
 int /*<<< orphan*/  dwc_otg_get_lpm_portsleepstatus (TYPE_19__*) ; 
 int /*<<< orphan*/  dwc_otg_hcd_is_b_host (TYPE_18__*) ; 
 int dwc_otg_hcd_otg_port (TYPE_18__*) ; 
 int /*<<< orphan*/  dwc_otg_host_hibernation_restore (TYPE_19__*,int /*<<< orphan*/ ,int) ; 
 void* dwc_otg_read_hprt0 (TYPE_19__*) ; 
 int /*<<< orphan*/  dwc_otg_save_global_regs (TYPE_19__*) ; 
 int /*<<< orphan*/  dwc_otg_save_host_regs (TYPE_19__*) ; 
 int /*<<< orphan*/  dwc_udelay (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_18__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_18__*) ; 

int dwc_otg_hcd_hub_control(dwc_otg_hcd_t * dwc_otg_hcd,
			    uint16_t typeReq,
			    uint16_t wValue,
			    uint16_t wIndex, uint8_t * buf, uint16_t wLength)
{
	int retval = 0;

	dwc_otg_core_if_t *core_if = dwc_otg_hcd->core_if;
	usb_hub_descriptor_t *hub_desc;
	hprt0_data_t hprt0 = {.d32 = 0 };

	uint32_t port_status;

	switch (typeReq) {
	case UCR_CLEAR_HUB_FEATURE:
		DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD HUB CONTROL - "
			    "ClearHubFeature 0x%x\n", wValue);
		switch (wValue) {
		case UHF_C_HUB_LOCAL_POWER:
		case UHF_C_HUB_OVER_CURRENT:
			/* Nothing required here */
			break;
		default:
			retval = -DWC_E_INVALID;
			DWC_ERROR("DWC OTG HCD - "
				  "ClearHubFeature request %xh unknown\n",
				  wValue);
		}
		break;
	case UCR_CLEAR_PORT_FEATURE:
#ifdef CONFIG_USB_DWC_OTG_LPM
		if (wValue != UHF_PORT_L1)
#endif
			if (!wIndex || wIndex > 1)
				goto error;

		switch (wValue) {
		case UHF_PORT_ENABLE:
			DWC_DEBUGPL(DBG_ANY, "DWC OTG HCD HUB CONTROL - "
				    "ClearPortFeature USB_PORT_FEAT_ENABLE\n");
			hprt0.d32 = dwc_otg_read_hprt0(core_if);
			hprt0.b.prtena = 1;
			DWC_WRITE_REG32(core_if->host_if->hprt0, hprt0.d32);
			break;
		case UHF_PORT_SUSPEND:
			DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD HUB CONTROL - "
				    "ClearPortFeature USB_PORT_FEAT_SUSPEND\n");

			if (core_if->power_down == 2) {
				dwc_otg_host_hibernation_restore(core_if, 0, 0);
			} else {
				DWC_WRITE_REG32(core_if->pcgcctl, 0);
				dwc_mdelay(5);

				hprt0.d32 = dwc_otg_read_hprt0(core_if);
				hprt0.b.prtres = 1;
				DWC_WRITE_REG32(core_if->host_if->hprt0, hprt0.d32);
				hprt0.b.prtsusp = 0;
				/* Clear Resume bit */
				dwc_mdelay(100);
				hprt0.b.prtres = 0;
				DWC_WRITE_REG32(core_if->host_if->hprt0, hprt0.d32);
			}
			break;
#ifdef CONFIG_USB_DWC_OTG_LPM
		case UHF_PORT_L1:
			{
				pcgcctl_data_t pcgcctl = {.d32 = 0 };
				glpmcfg_data_t lpmcfg = {.d32 = 0 };

				lpmcfg.d32 =
				    DWC_READ_REG32(&core_if->
						   core_global_regs->glpmcfg);
				lpmcfg.b.en_utmi_sleep = 0;
				lpmcfg.b.hird_thres &= (~(1 << 4));
				lpmcfg.b.prt_sleep_sts = 1;
				DWC_WRITE_REG32(&core_if->
						core_global_regs->glpmcfg,
						lpmcfg.d32);

				/* Clear Enbl_L1Gating bit. */
				pcgcctl.b.enbl_sleep_gating = 1;
				DWC_MODIFY_REG32(core_if->pcgcctl, pcgcctl.d32,
						 0);

				dwc_mdelay(5);

				hprt0.d32 = dwc_otg_read_hprt0(core_if);
				hprt0.b.prtres = 1;
				DWC_WRITE_REG32(core_if->host_if->hprt0,
						hprt0.d32);
				/* This bit will be cleared in wakeup interrupt handle */
				break;
			}
#endif
		case UHF_PORT_POWER:
			DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD HUB CONTROL - "
				    "ClearPortFeature USB_PORT_FEAT_POWER\n");
			hprt0.d32 = dwc_otg_read_hprt0(core_if);
			hprt0.b.prtpwr = 0;
			DWC_WRITE_REG32(core_if->host_if->hprt0, hprt0.d32);
			break;
		case UHF_PORT_INDICATOR:
			DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD HUB CONTROL - "
				    "ClearPortFeature USB_PORT_FEAT_INDICATOR\n");
			/* Port inidicator not supported */
			break;
		case UHF_C_PORT_CONNECTION:
			/* Clears drivers internal connect status change
			 * flag */
			DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD HUB CONTROL - "
				    "ClearPortFeature USB_PORT_FEAT_C_CONNECTION\n");
			dwc_otg_hcd->flags.b.port_connect_status_change = 0;
			break;
		case UHF_C_PORT_RESET:
			/* Clears the driver's internal Port Reset Change
			 * flag */
			DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD HUB CONTROL - "
				    "ClearPortFeature USB_PORT_FEAT_C_RESET\n");
			dwc_otg_hcd->flags.b.port_reset_change = 0;
			break;
		case UHF_C_PORT_ENABLE:
			/* Clears the driver's internal Port
			 * Enable/Disable Change flag */
			DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD HUB CONTROL - "
				    "ClearPortFeature USB_PORT_FEAT_C_ENABLE\n");
			dwc_otg_hcd->flags.b.port_enable_change = 0;
			break;
		case UHF_C_PORT_SUSPEND:
			/* Clears the driver's internal Port Suspend
			 * Change flag, which is set when resume signaling on
			 * the host port is complete */
			DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD HUB CONTROL - "
				    "ClearPortFeature USB_PORT_FEAT_C_SUSPEND\n");
			dwc_otg_hcd->flags.b.port_suspend_change = 0;
			break;
#ifdef CONFIG_USB_DWC_OTG_LPM
		case UHF_C_PORT_L1:
			dwc_otg_hcd->flags.b.port_l1_change = 0;
			break;
#endif
		case UHF_C_PORT_OVER_CURRENT:
			DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD HUB CONTROL - "
				    "ClearPortFeature USB_PORT_FEAT_C_OVER_CURRENT\n");
			dwc_otg_hcd->flags.b.port_over_current_change = 0;
			break;
		default:
			retval = -DWC_E_INVALID;
			DWC_ERROR("DWC OTG HCD - "
				  "ClearPortFeature request %xh "
				  "unknown or unsupported\n", wValue);
		}
		break;
	case UCR_GET_HUB_DESCRIPTOR:
		DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD HUB CONTROL - "
			    "GetHubDescriptor\n");
		hub_desc = (usb_hub_descriptor_t *) buf;
		hub_desc->bDescLength = 9;
		hub_desc->bDescriptorType = 0x29;
		hub_desc->bNbrPorts = 1;
		USETW(hub_desc->wHubCharacteristics, 0x08);
		hub_desc->bPwrOn2PwrGood = 1;
		hub_desc->bHubContrCurrent = 0;
		hub_desc->DeviceRemovable[0] = 0;
		hub_desc->DeviceRemovable[1] = 0xff;
		break;
	case UCR_GET_HUB_STATUS:
		DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD HUB CONTROL - "
			    "GetHubStatus\n");
		DWC_MEMSET(buf, 0, 4);
		break;
	case UCR_GET_PORT_STATUS:
		DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD HUB CONTROL - "
			    "GetPortStatus wIndex = 0x%04x FLAGS=0x%08x\n",
			    wIndex, dwc_otg_hcd->flags.d32);
		if (!wIndex || wIndex > 1)
			goto error;

		port_status = 0;

		if (dwc_otg_hcd->flags.b.port_connect_status_change)
			port_status |= (1 << UHF_C_PORT_CONNECTION);

		if (dwc_otg_hcd->flags.b.port_enable_change)
			port_status |= (1 << UHF_C_PORT_ENABLE);

		if (dwc_otg_hcd->flags.b.port_suspend_change)
			port_status |= (1 << UHF_C_PORT_SUSPEND);

		if (dwc_otg_hcd->flags.b.port_l1_change)
			port_status |= (1 << UHF_C_PORT_L1);

		if (dwc_otg_hcd->flags.b.port_reset_change) {
			port_status |= (1 << UHF_C_PORT_RESET);
		}

		if (dwc_otg_hcd->flags.b.port_over_current_change) {
			DWC_WARN("Overcurrent change detected\n");
			port_status |= (1 << UHF_C_PORT_OVER_CURRENT);
		}

		if (!dwc_otg_hcd->flags.b.port_connect_status) {
			/*
			 * The port is disconnected, which means the core is
			 * either in device mode or it soon will be. Just
			 * return 0's for the remainder of the port status
			 * since the port register can't be read if the core
			 * is in device mode.
			 */
			*((__le32 *) buf) = dwc_cpu_to_le32(&port_status);
			break;
		}

		hprt0.d32 = DWC_READ_REG32(core_if->host_if->hprt0);
		DWC_DEBUGPL(DBG_HCDV, "  HPRT0: 0x%08x\n", hprt0.d32);

		if (hprt0.b.prtconnsts)
			port_status |= (1 << UHF_PORT_CONNECTION);

		if (hprt0.b.prtena)
			port_status |= (1 << UHF_PORT_ENABLE);

		if (hprt0.b.prtsusp)
			port_status |= (1 << UHF_PORT_SUSPEND);

		if (hprt0.b.prtovrcurract)
			port_status |= (1 << UHF_PORT_OVER_CURRENT);

		if (hprt0.b.prtrst)
			port_status |= (1 << UHF_PORT_RESET);

		if (hprt0.b.prtpwr)
			port_status |= (1 << UHF_PORT_POWER);

		if (hprt0.b.prtspd == DWC_HPRT0_PRTSPD_HIGH_SPEED)
			port_status |= (1 << UHF_PORT_HIGH_SPEED);
		else if (hprt0.b.prtspd == DWC_HPRT0_PRTSPD_LOW_SPEED)
			port_status |= (1 << UHF_PORT_LOW_SPEED);

		if (hprt0.b.prttstctl)
			port_status |= (1 << UHF_PORT_TEST);
		if (dwc_otg_get_lpm_portsleepstatus(dwc_otg_hcd->core_if)) {
			port_status |= (1 << UHF_PORT_L1);
		}
		/*
		   For Synopsys HW emulation of Power down wkup_control asserts the
		   hreset_n and prst_n on suspned. This causes the HPRT0 to be zero.
		   We intentionally tell the software that port is in L2Suspend state.
		   Only for STE.
		*/
		if ((core_if->power_down == 2)
		    && (core_if->hibernation_suspend == 1)) {
			port_status |= (1 << UHF_PORT_SUSPEND);
		}
		/* USB_PORT_FEAT_INDICATOR unsupported always 0 */

		*((__le32 *) buf) = dwc_cpu_to_le32(&port_status);

		break;
	case UCR_SET_HUB_FEATURE:
		DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD HUB CONTROL - "
			    "SetHubFeature\n");
		/* No HUB features supported */
		break;
	case UCR_SET_PORT_FEATURE:
		if (wValue != UHF_PORT_TEST && (!wIndex || wIndex > 1))
			goto error;

		if (!dwc_otg_hcd->flags.b.port_connect_status) {
			/*
			 * The port is disconnected, which means the core is
			 * either in device mode or it soon will be. Just
			 * return without doing anything since the port
			 * register can't be written if the core is in device
			 * mode.
			 */
			break;
		}

		switch (wValue) {
		case UHF_PORT_SUSPEND:
			DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD HUB CONTROL - "
				    "SetPortFeature - USB_PORT_FEAT_SUSPEND\n");
			if (dwc_otg_hcd_otg_port(dwc_otg_hcd) != wIndex) {
				goto error;
			}
			if (core_if->power_down == 2) {
				int timeout = 300;
				dwc_irqflags_t flags;
				pcgcctl_data_t pcgcctl = {.d32 = 0 };
				gpwrdn_data_t gpwrdn = {.d32 = 0 };
				gusbcfg_data_t gusbcfg = {.d32 = 0 };
#ifdef DWC_DEV_SRPCAP
				int32_t otg_cap_param = core_if->core_params->otg_cap;
#endif
				DWC_PRINTF("Preparing for complete power-off\n");

				/* Save registers before hibernation */
				dwc_otg_save_global_regs(core_if);
				dwc_otg_save_host_regs(core_if);

				hprt0.d32 = dwc_otg_read_hprt0(core_if);
				hprt0.b.prtsusp = 1;
				hprt0.b.prtena = 0;
				DWC_WRITE_REG32(core_if->host_if->hprt0, hprt0.d32);
				/* Spin hprt0.b.prtsusp to became 1 */
				do {
					hprt0.d32 = dwc_otg_read_hprt0(core_if);
					if (hprt0.b.prtsusp) {
						break;
					}
					dwc_mdelay(1);
				} while (--timeout);
				if (!timeout) {
					DWC_WARN("Suspend wasn't genereted\n");
				}
				dwc_udelay(10);

				/*
				 * We need to disable interrupts to prevent servicing of any IRQ
				 * during going to hibernation
				 */
				DWC_SPINLOCK_IRQSAVE(dwc_otg_hcd->lock, &flags);
				core_if->lx_state = DWC_OTG_L2;
#ifdef DWC_DEV_SRPCAP
				hprt0.d32 = dwc_otg_read_hprt0(core_if);
				hprt0.b.prtpwr = 0;
				hprt0.b.prtena = 0;
				DWC_WRITE_REG32(core_if->host_if->hprt0,
						hprt0.d32);
#endif
				gusbcfg.d32 =
				    DWC_READ_REG32(&core_if->core_global_regs->
						   gusbcfg);
				if (gusbcfg.b.ulpi_utmi_sel == 1) {
					/* ULPI interface */
					/* Suspend the Phy Clock */
					pcgcctl.d32 = 0;
					pcgcctl.b.stoppclk = 1;
					DWC_MODIFY_REG32(core_if->pcgcctl, 0,
							 pcgcctl.d32);
					dwc_udelay(10);
					gpwrdn.b.pmuactv = 1;
					DWC_MODIFY_REG32(&core_if->
							 core_global_regs->
							 gpwrdn, 0, gpwrdn.d32);
				} else {
					/* UTMI+ Interface */
					gpwrdn.b.pmuactv = 1;
					DWC_MODIFY_REG32(&core_if->
							 core_global_regs->
							 gpwrdn, 0, gpwrdn.d32);
					dwc_udelay(10);
					pcgcctl.b.stoppclk = 1;
					DWC_MODIFY_REG32(core_if->pcgcctl, 0, pcgcctl.d32);
					dwc_udelay(10);
				}
#ifdef DWC_DEV_SRPCAP
				gpwrdn.d32 = 0;
				gpwrdn.b.dis_vbus = 1;
				DWC_MODIFY_REG32(&core_if->core_global_regs->
						 gpwrdn, 0, gpwrdn.d32);
#endif
				gpwrdn.d32 = 0;
				gpwrdn.b.pmuintsel = 1;
				DWC_MODIFY_REG32(&core_if->core_global_regs->
						 gpwrdn, 0, gpwrdn.d32);
				dwc_udelay(10);

				gpwrdn.d32 = 0;
#ifdef DWC_DEV_SRPCAP
				gpwrdn.b.srp_det_msk = 1;
#endif
				gpwrdn.b.disconn_det_msk = 1;
				gpwrdn.b.lnstchng_msk = 1;
				gpwrdn.b.sts_chngint_msk = 1;
				DWC_MODIFY_REG32(&core_if->core_global_regs->
						 gpwrdn, 0, gpwrdn.d32);
				dwc_udelay(10);

				/* Enable Power Down Clamp and all interrupts in GPWRDN */
				gpwrdn.d32 = 0;
				gpwrdn.b.pwrdnclmp = 1;
				DWC_MODIFY_REG32(&core_if->core_global_regs->
						 gpwrdn, 0, gpwrdn.d32);
				dwc_udelay(10);

				/* Switch off VDD */
				gpwrdn.d32 = 0;
				gpwrdn.b.pwrdnswtch = 1;
				DWC_MODIFY_REG32(&core_if->core_global_regs->
						 gpwrdn, 0, gpwrdn.d32);

#ifdef DWC_DEV_SRPCAP
				if (otg_cap_param == DWC_OTG_CAP_PARAM_HNP_SRP_CAPABLE)
				{
					core_if->pwron_timer_started = 1;
					DWC_TIMER_SCHEDULE(core_if->pwron_timer, 6000 /* 6 secs */ );
				}
#endif
				/* Save gpwrdn register for further usage if stschng interrupt */
				core_if->gr_backup->gpwrdn_local =
						DWC_READ_REG32(&core_if->core_global_regs->gpwrdn);

				/* Set flag to indicate that we are in hibernation */
				core_if->hibernation_suspend = 1;
				DWC_SPINUNLOCK_IRQRESTORE(dwc_otg_hcd->lock,flags);

				DWC_PRINTF("Host hibernation completed\n");
				// Exit from case statement
				break;

			}
			if (dwc_otg_hcd_otg_port(dwc_otg_hcd) == wIndex &&
			    dwc_otg_hcd->fops->get_b_hnp_enable(dwc_otg_hcd)) {
				gotgctl_data_t gotgctl = {.d32 = 0 };
				gotgctl.b.hstsethnpen = 1;
				DWC_MODIFY_REG32(&core_if->core_global_regs->
						 gotgctl, 0, gotgctl.d32);
				core_if->op_state = A_SUSPEND;
			}
			hprt0.d32 = dwc_otg_read_hprt0(core_if);
			hprt0.b.prtsusp = 1;
			DWC_WRITE_REG32(core_if->host_if->hprt0, hprt0.d32);
			{
				dwc_irqflags_t flags;
				/* Update lx_state */
				DWC_SPINLOCK_IRQSAVE(dwc_otg_hcd->lock, &flags);
				core_if->lx_state = DWC_OTG_L2;
				DWC_SPINUNLOCK_IRQRESTORE(dwc_otg_hcd->lock, flags);
			}
			/* Suspend the Phy Clock */
			{
				pcgcctl_data_t pcgcctl = {.d32 = 0 };
				pcgcctl.b.stoppclk = 1;
				DWC_MODIFY_REG32(core_if->pcgcctl, 0,
						 pcgcctl.d32);
				dwc_udelay(10);
			}

			/* For HNP the bus must be suspended for at least 200ms. */
			if (dwc_otg_hcd->fops->get_b_hnp_enable(dwc_otg_hcd)) {
				pcgcctl_data_t pcgcctl = {.d32 = 0 };
				pcgcctl.b.stoppclk = 1;
                DWC_MODIFY_REG32(core_if->pcgcctl, pcgcctl.d32, 0);
				dwc_mdelay(200);
			}

			/** @todo - check how sw can wait for 1 sec to check asesvld??? */
#if 0 //vahrama !!!!!!!!!!!!!!!!!!
			if (core_if->adp_enable) {
				gotgctl_data_t gotgctl = {.d32 = 0 };
				gpwrdn_data_t gpwrdn;

				while (gotgctl.b.asesvld == 1) {
					gotgctl.d32 =
					    DWC_READ_REG32(&core_if->
							   core_global_regs->
							   gotgctl);
					dwc_mdelay(100);
				}

				/* Enable Power Down Logic */
				gpwrdn.d32 = 0;
				gpwrdn.b.pmuactv = 1;
				DWC_MODIFY_REG32(&core_if->core_global_regs->
						 gpwrdn, 0, gpwrdn.d32);

				/* Unmask SRP detected interrupt from Power Down Logic */
				gpwrdn.d32 = 0;
				gpwrdn.b.srp_det_msk = 1;
				DWC_MODIFY_REG32(&core_if->core_global_regs->
						 gpwrdn, 0, gpwrdn.d32);

				dwc_otg_adp_probe_start(core_if);
			}
#endif
			break;
		case UHF_PORT_POWER:
			DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD HUB CONTROL - "
				    "SetPortFeature - USB_PORT_FEAT_POWER\n");
			hprt0.d32 = dwc_otg_read_hprt0(core_if);
			hprt0.b.prtpwr = 1;
			DWC_WRITE_REG32(core_if->host_if->hprt0, hprt0.d32);
			break;
		case UHF_PORT_RESET:
			if ((core_if->power_down == 2)
			    && (core_if->hibernation_suspend == 1)) {
				/* If we are going to exit from Hibernated
				 * state via USB RESET.
				 */
				dwc_otg_host_hibernation_restore(core_if, 0, 1);
			} else {
				hprt0.d32 = dwc_otg_read_hprt0(core_if);

				DWC_DEBUGPL(DBG_HCD,
					    "DWC OTG HCD HUB CONTROL - "
					    "SetPortFeature - USB_PORT_FEAT_RESET\n");
				{
					pcgcctl_data_t pcgcctl = {.d32 = 0 };
					pcgcctl.b.enbl_sleep_gating = 1;
					pcgcctl.b.stoppclk = 1;
					DWC_MODIFY_REG32(core_if->pcgcctl, pcgcctl.d32, 0);
					DWC_WRITE_REG32(core_if->pcgcctl, 0);
				}
#ifdef CONFIG_USB_DWC_OTG_LPM
				{
					glpmcfg_data_t lpmcfg;
					lpmcfg.d32 =
						DWC_READ_REG32(&core_if->core_global_regs->glpmcfg);
					if (lpmcfg.b.prt_sleep_sts) {
						lpmcfg.b.en_utmi_sleep = 0;
						lpmcfg.b.hird_thres &= (~(1 << 4));
						DWC_WRITE_REG32
						    (&core_if->core_global_regs->glpmcfg,
						     lpmcfg.d32);
						dwc_mdelay(1);
					}
				}
#endif
				hprt0.d32 = dwc_otg_read_hprt0(core_if);
				/* Clear suspend bit if resetting from suspended state. */
				hprt0.b.prtsusp = 0;
				/* When B-Host the Port reset bit is set in
				 * the Start HCD Callback function, so that
				 * the reset is started within 1ms of the HNP
				 * success interrupt. */
				if (!dwc_otg_hcd_is_b_host(dwc_otg_hcd)) {
					hprt0.b.prtpwr = 1;
					hprt0.b.prtrst = 1;
					DWC_PRINTF("Indeed it is in host mode hprt0 = %08x\n",hprt0.d32);
					DWC_WRITE_REG32(core_if->host_if->hprt0,
							hprt0.d32);
				}
				/* Clear reset bit in 10ms (FS/LS) or 50ms (HS) */
				dwc_mdelay(60);
				hprt0.b.prtrst = 0;
				DWC_WRITE_REG32(core_if->host_if->hprt0, hprt0.d32);
				core_if->lx_state = DWC_OTG_L0;	/* Now back to the on state */
			}
			break;
#ifdef DWC_HS_ELECT_TST
		case UHF_PORT_TEST:
			{
				uint32_t t;
				gintmsk_data_t gintmsk;

				t = (wIndex >> 8);	/* MSB wIndex USB */
				DWC_DEBUGPL(DBG_HCD,
					    "DWC OTG HCD HUB CONTROL - "
					    "SetPortFeature - USB_PORT_FEAT_TEST %d\n",
					    t);
				DWC_WARN("USB_PORT_FEAT_TEST %d\n", t);
				if (t < 6) {
					hprt0.d32 = dwc_otg_read_hprt0(core_if);
					hprt0.b.prttstctl = t;
					DWC_WRITE_REG32(core_if->host_if->hprt0,
							hprt0.d32);
				} else {
					/* Setup global vars with reg addresses (quick and
					 * dirty hack, should be cleaned up)
					 */
					global_regs = core_if->core_global_regs;
					hc_global_regs =
					    core_if->host_if->host_global_regs;
					hc_regs =
					    (dwc_otg_hc_regs_t *) ((char *)
								   global_regs +
								   0x500);
					data_fifo =
					    (uint32_t *) ((char *)global_regs +
							  0x1000);

					if (t == 6) {	/* HS_HOST_PORT_SUSPEND_RESUME */
						/* Save current interrupt mask */
						gintmsk.d32 =
						    DWC_READ_REG32
						    (&global_regs->gintmsk);

						/* Disable all interrupts while we muck with
						 * the hardware directly
						 */
						DWC_WRITE_REG32(&global_regs->gintmsk, 0);

						/* 15 second delay per the test spec */
						dwc_mdelay(15000);

						/* Drive suspend on the root port */
						hprt0.d32 =
						    dwc_otg_read_hprt0(core_if);
						hprt0.b.prtsusp = 1;
						hprt0.b.prtres = 0;
						DWC_WRITE_REG32(core_if->host_if->hprt0, hprt0.d32);

						/* 15 second delay per the test spec */
						dwc_mdelay(15000);

						/* Drive resume on the root port */
						hprt0.d32 =
						    dwc_otg_read_hprt0(core_if);
						hprt0.b.prtsusp = 0;
						hprt0.b.prtres = 1;
						DWC_WRITE_REG32(core_if->host_if->hprt0, hprt0.d32);
						dwc_mdelay(100);

						/* Clear the resume bit */
						hprt0.b.prtres = 0;
						DWC_WRITE_REG32(core_if->host_if->hprt0, hprt0.d32);

						/* Restore interrupts */
						DWC_WRITE_REG32(&global_regs->gintmsk, gintmsk.d32);
					} else if (t == 7) {	/* SINGLE_STEP_GET_DEVICE_DESCRIPTOR setup */
						/* Save current interrupt mask */
						gintmsk.d32 =
						    DWC_READ_REG32
						    (&global_regs->gintmsk);

						/* Disable all interrupts while we muck with
						 * the hardware directly
						 */
						DWC_WRITE_REG32(&global_regs->gintmsk, 0);

						/* 15 second delay per the test spec */
						dwc_mdelay(15000);

						/* Send the Setup packet */
						do_setup();

						/* 15 second delay so nothing else happens for awhile */
						dwc_mdelay(15000);

						/* Restore interrupts */
						DWC_WRITE_REG32(&global_regs->gintmsk, gintmsk.d32);
					} else if (t == 8) {	/* SINGLE_STEP_GET_DEVICE_DESCRIPTOR execute */
						/* Save current interrupt mask */
						gintmsk.d32 =
						    DWC_READ_REG32
						    (&global_regs->gintmsk);

						/* Disable all interrupts while we muck with
						 * the hardware directly
						 */
						DWC_WRITE_REG32(&global_regs->gintmsk, 0);

						/* Send the Setup packet */
						do_setup();

						/* 15 second delay so nothing else happens for awhile */
						dwc_mdelay(15000);

						/* Send the In and Ack packets */
						do_in_ack();

						/* 15 second delay so nothing else happens for awhile */
						dwc_mdelay(15000);

						/* Restore interrupts */
						DWC_WRITE_REG32(&global_regs->gintmsk, gintmsk.d32);
					}
				}
				break;
			}
#endif /* DWC_HS_ELECT_TST */

		case UHF_PORT_INDICATOR:
			DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD HUB CONTROL - "
				    "SetPortFeature - USB_PORT_FEAT_INDICATOR\n");
			/* Not supported */
			break;
		default:
			retval = -DWC_E_INVALID;
			DWC_ERROR("DWC OTG HCD - "
				  "SetPortFeature request %xh "
				  "unknown or unsupported\n", wValue);
			break;
		}
		break;
#ifdef CONFIG_USB_DWC_OTG_LPM
	case UCR_SET_AND_TEST_PORT_FEATURE:
		if (wValue != UHF_PORT_L1) {
			goto error;
		}
		{
			int portnum, hird, devaddr, remwake;
			glpmcfg_data_t lpmcfg;
			uint32_t time_usecs;
			gintsts_data_t gintsts;
			gintmsk_data_t gintmsk;

			if (!dwc_otg_get_param_lpm_enable(core_if)) {
				goto error;
			}
			if (wValue != UHF_PORT_L1 || wLength != 1) {
				goto error;
			}
			/* Check if the port currently is in SLEEP state */
			lpmcfg.d32 =
			    DWC_READ_REG32(&core_if->core_global_regs->glpmcfg);
			if (lpmcfg.b.prt_sleep_sts) {
				DWC_INFO("Port is already in sleep mode\n");
				buf[0] = 0;	/* Return success */
				break;
			}

			portnum = wIndex & 0xf;
			hird = (wIndex >> 4) & 0xf;
			devaddr = (wIndex >> 8) & 0x7f;
			remwake = (wIndex >> 15);

			if (portnum != 1) {
				retval = -DWC_E_INVALID;
				DWC_WARN
				    ("Wrong port number(%d) in SetandTestPortFeature request\n",
				     portnum);
				break;
			}

			DWC_PRINTF
			    ("SetandTestPortFeature request: portnum = %d, hird = %d, devaddr = %d, rewake = %d\n",
			     portnum, hird, devaddr, remwake);
			/* Disable LPM interrupt */
			gintmsk.d32 = 0;
			gintmsk.b.lpmtranrcvd = 1;
			DWC_MODIFY_REG32(&core_if->core_global_regs->gintmsk,
					 gintmsk.d32, 0);

			if (dwc_otg_hcd_send_lpm
			    (dwc_otg_hcd, devaddr, hird, remwake)) {
				retval = -DWC_E_INVALID;
				break;
			}

			time_usecs = 10 * (lpmcfg.b.retry_count + 1);
			/* We will consider timeout if time_usecs microseconds pass,
			 * and we don't receive LPM transaction status.
			 * After receiving non-error responce(ACK/NYET/STALL) from device,
			 *  core will set lpmtranrcvd bit.
			 */
			do {
				gintsts.d32 =
				    DWC_READ_REG32(&core_if->core_global_regs->gintsts);
				if (gintsts.b.lpmtranrcvd) {
					break;
				}
				dwc_udelay(1);
			} while (--time_usecs);
			/* lpm_int bit will be cleared in LPM interrupt handler */

			/* Now fill status
			 * 0x00 - Success
			 * 0x10 - NYET
			 * 0x11 - Timeout
			 */
			if (!gintsts.b.lpmtranrcvd) {
				buf[0] = 0x3;	/* Completion code is Timeout */
				dwc_otg_hcd_free_hc_from_lpm(dwc_otg_hcd);
			} else {
				lpmcfg.d32 =
				    DWC_READ_REG32(&core_if->core_global_regs->glpmcfg);
				if (lpmcfg.b.lpm_resp == 0x3) {
					/* ACK responce from the device */
					buf[0] = 0x00;	/* Success */
				} else if (lpmcfg.b.lpm_resp == 0x2) {
					/* NYET responce from the device */
					buf[0] = 0x2;
				} else {
					/* Otherwise responce with Timeout */
					buf[0] = 0x3;
				}
			}
			DWC_PRINTF("Device responce to LPM trans is %x\n",
				   lpmcfg.b.lpm_resp);
			DWC_MODIFY_REG32(&core_if->core_global_regs->gintmsk, 0,
					 gintmsk.d32);

			break;
		}
#endif /* CONFIG_USB_DWC_OTG_LPM */
	default:
error:
		retval = -DWC_E_INVALID;
		DWC_WARN("DWC OTG HCD - "
			 "Unknown hub control request type or invalid typeReq: %xh wIndex: %xh wValue: %xh\n",
			 typeReq, wIndex, wValue);
		break;
	}

	return retval;
}