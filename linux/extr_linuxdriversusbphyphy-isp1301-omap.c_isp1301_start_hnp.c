#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct usb_otg {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int
isp1301_start_hnp(struct usb_otg *otg)
{
#ifdef	CONFIG_USB_OTG
	struct isp1301	*isp = container_of(otg->usb_phy, struct isp1301, phy);
	u32 l;

	if (isp != the_transceiver)
		return -ENODEV;
	if (otg->default_a && (otg->host == NULL || !otg->host->b_hnp_enable))
		return -ENOTCONN;
	if (!otg->default_a && (otg->gadget == NULL
			|| !otg->gadget->b_hnp_enable))
		return -ENOTCONN;

	/* We want hardware to manage most HNP protocol timings.
	 * So do this part as early as possible...
	 */
	switch (isp->phy.otg->state) {
	case OTG_STATE_B_HOST:
		isp->phy.otg->state = OTG_STATE_B_PERIPHERAL;
		/* caller will suspend next */
		break;
	case OTG_STATE_A_HOST:
#if 0
		/* autoconnect mode avoids irq latency bugs */
		isp1301_set_bits(isp, ISP1301_MODE_CONTROL_1,
				MC1_BDIS_ACON_EN);
#endif
		/* caller must suspend then clear A_BUSREQ */
		usb_gadget_vbus_connect(otg->gadget);
		l = omap_readl(OTG_CTRL);
		l |= OTG_A_SETB_HNPEN;
		omap_writel(l, OTG_CTRL);

		break;
	case OTG_STATE_A_PERIPHERAL:
		/* initiated by B-Host suspend */
		break;
	default:
		return -EILSEQ;
	}
	pr_debug("otg: HNP %s, %06x ...\n",
		state_name(isp), omap_readl(OTG_CTRL));
	check_state(isp, __func__);
	return 0;
#else
	/* srp-only */
	return -EINVAL;
#endif
}