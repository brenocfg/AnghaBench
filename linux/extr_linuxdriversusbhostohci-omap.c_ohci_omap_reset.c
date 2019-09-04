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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {scalar_t__ otg_port; int /*<<< orphan*/  controller; } ;
struct usb_hcd {int power_budget; TYPE_1__ self; } ;
struct omap_usb_config {scalar_t__ otg; scalar_t__ rwc; int /*<<< orphan*/  (* ocpi_enable ) () ;} ;
struct ohci_hcd {int /*<<< orphan*/  flags; TYPE_3__* regs; int /*<<< orphan*/  hc_control; } ;
struct TYPE_8__ {int power_budget; } ;
struct TYPE_6__ {int /*<<< orphan*/  a; } ;
struct TYPE_7__ {TYPE_2__ roothub; int /*<<< orphan*/  control; } ;

/* Variables and functions */
 int /*<<< orphan*/  OHCI_CTRL_RWC ; 
 int /*<<< orphan*/  OHCI_QUIRK_HUB_POWER ; 
 int /*<<< orphan*/  RH_A_NOCP ; 
 int /*<<< orphan*/  RH_A_NPS ; 
 int /*<<< orphan*/  W4_USB_HIGHZ ; 
 int /*<<< orphan*/  W8_1610_GPIO9 ; 
 scalar_t__ cpu_is_omap15xx () ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct omap_usb_config* dev_get_platdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_direction_input (int) ; 
 int /*<<< orphan*/  gpio_request (int,char*) ; 
 struct ohci_hcd* hcd_to_ohci (struct usb_hcd*) ; 
 scalar_t__ machine_is_nokia770 () ; 
 scalar_t__ machine_is_omap_h2 () ; 
 scalar_t__ machine_is_omap_h3 () ; 
 scalar_t__ machine_is_omap_innovator () ; 
 scalar_t__ machine_is_omap_osk () ; 
 int ohci_setup (struct usb_hcd*) ; 
 TYPE_4__* ohci_to_hcd (struct ohci_hcd*) ; 
 int /*<<< orphan*/  ohci_writel (struct ohci_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap_1510_local_bus_init () ; 
 int /*<<< orphan*/  omap_1510_local_bus_power (int) ; 
 int /*<<< orphan*/  omap_cfg_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_ohci_clock_power (int) ; 
 int /*<<< orphan*/  omap_ohci_transceiver_power (int) ; 
 int /*<<< orphan*/  roothub_a (struct ohci_hcd*) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ohci_omap_reset(struct usb_hcd *hcd)
{
	struct ohci_hcd		*ohci = hcd_to_ohci(hcd);
	struct omap_usb_config	*config = dev_get_platdata(hcd->self.controller);
	int			need_transceiver = (config->otg != 0);
	int			ret;

	dev_dbg(hcd->self.controller, "starting USB Controller\n");

	if (config->otg) {
		hcd->self.otg_port = config->otg;
		/* default/minimum OTG power budget:  8 mA */
		hcd->power_budget = 8;
	}

	/* boards can use OTG transceivers in non-OTG modes */
	need_transceiver = need_transceiver
			|| machine_is_omap_h2() || machine_is_omap_h3();

	/* XXX OMAP16xx only */
	if (config->ocpi_enable)
		config->ocpi_enable();

#ifdef	CONFIG_USB_OTG
	if (need_transceiver) {
		hcd->usb_phy = usb_get_phy(USB_PHY_TYPE_USB2);
		if (!IS_ERR_OR_NULL(hcd->usb_phy)) {
			int	status = otg_set_host(hcd->usb_phy->otg,
						&ohci_to_hcd(ohci)->self);
			dev_dbg(hcd->self.controller, "init %s phy, status %d\n",
					hcd->usb_phy->label, status);
			if (status) {
				usb_put_phy(hcd->usb_phy);
				return status;
			}
		} else {
			return -EPROBE_DEFER;
		}
		hcd->skip_phy_initialization = 1;
		ohci->start_hnp = start_hnp;
	}
#endif

	omap_ohci_clock_power(1);

	if (cpu_is_omap15xx()) {
		omap_1510_local_bus_power(1);
		omap_1510_local_bus_init();
	}

	ret = ohci_setup(hcd);
	if (ret < 0)
		return ret;

	if (config->otg || config->rwc) {
		ohci->hc_control = OHCI_CTRL_RWC;
		writel(OHCI_CTRL_RWC, &ohci->regs->control);
	}

	/* board-specific power switching and overcurrent support */
	if (machine_is_omap_osk() || machine_is_omap_innovator()) {
		u32	rh = roothub_a (ohci);

		/* power switching (ganged by default) */
		rh &= ~RH_A_NPS;

		/* TPS2045 switch for internal transceiver (port 1) */
		if (machine_is_omap_osk()) {
			ohci_to_hcd(ohci)->power_budget = 250;

			rh &= ~RH_A_NOCP;

			/* gpio9 for overcurrent detction */
			omap_cfg_reg(W8_1610_GPIO9);
			gpio_request(9, "OHCI overcurrent");
			gpio_direction_input(9);

			/* for paranoia's sake:  disable USB.PUEN */
			omap_cfg_reg(W4_USB_HIGHZ);
		}
		ohci_writel(ohci, rh, &ohci->regs->roothub.a);
		ohci->flags &= ~OHCI_QUIRK_HUB_POWER;
	} else if (machine_is_nokia770()) {
		/* We require a self-powered hub, which should have
		 * plenty of power. */
		ohci_to_hcd(ohci)->power_budget = 0;
	}

	/* FIXME hub_wq hub requests should manage power switching */
	omap_ohci_transceiver_power(1);

	/* board init will have already handled HMC and mux setup.
	 * any external transceiver should already be initialized
	 * too, so all configured ports use the right signaling now.
	 */

	return 0;
}