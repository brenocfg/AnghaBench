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
struct oxnas_hcd {int /*<<< orphan*/  clk; int /*<<< orphan*/  syscon; scalar_t__ use_phya; scalar_t__ use_pllb; int /*<<< orphan*/  rst_phyb; int /*<<< orphan*/  rst_phya; int /*<<< orphan*/  rst_host; int /*<<< orphan*/  phyref; int /*<<< orphan*/  refsrc; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLLB_DIV_CTRL_REGOFFSET ; 
 unsigned long PLLB_DIV_FRAC (int /*<<< orphan*/ ) ; 
 unsigned long PLLB_DIV_INT (int) ; 
 unsigned long REF300_DIV_FRAC (int /*<<< orphan*/ ) ; 
 unsigned long REF300_DIV_INT (int) ; 
 int /*<<< orphan*/  REF300_DIV_REGOFFSET ; 
 int /*<<< orphan*/  USBAMUX_DEVICE ; 
 int /*<<< orphan*/  USBHSPHY_CTRL_REGOFFSET ; 
 unsigned long USBHSPHY_TEST_ADD ; 
 unsigned long USBHSPHY_TEST_CLK ; 
 int USBHSPHY_TEST_DIN ; 
 unsigned long USB_CLK_INTERNAL ; 
 int /*<<< orphan*/  USB_CTRL_REGOFFSET ; 
 unsigned long USB_INT_CLK_PLLB ; 
 unsigned long USB_INT_CLK_REF300 ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned long) ; 
 int /*<<< orphan*/  reset_control_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void start_oxnas_usb_ehci(struct oxnas_hcd *oxnas)
{
	if (oxnas->use_pllb) {
		/* enable pllb */
		clk_prepare_enable(oxnas->refsrc);
		/* enable ref600 */
		clk_prepare_enable(oxnas->phyref);
		/* 600MHz pllb divider for 12MHz */
		regmap_write_bits(oxnas->syscon, PLLB_DIV_CTRL_REGOFFSET, 0xffff, PLLB_DIV_INT(50) | PLLB_DIV_FRAC(0));
	} else {
		/* ref 300 divider for 12MHz */
		regmap_write_bits(oxnas->syscon, REF300_DIV_REGOFFSET, 0xffff, REF300_DIV_INT(25) | REF300_DIV_FRAC(0));
	}

	/* Ensure the USB block is properly reset */
	reset_control_reset(oxnas->rst_host);
	reset_control_reset(oxnas->rst_phya);
	reset_control_reset(oxnas->rst_phyb);

	/* Force the high speed clock to be generated all the time, via serial
	 programming of the USB HS PHY */
	regmap_write_bits(oxnas->syscon, USBHSPHY_CTRL_REGOFFSET, 0xffff,
			  (2UL << USBHSPHY_TEST_ADD) |
			  (0xe0UL << USBHSPHY_TEST_DIN));

	regmap_write_bits(oxnas->syscon, USBHSPHY_CTRL_REGOFFSET, 0xffff,
			  (1UL << USBHSPHY_TEST_CLK) |
			  (2UL << USBHSPHY_TEST_ADD) |
			  (0xe0UL << USBHSPHY_TEST_DIN));

	regmap_write_bits(oxnas->syscon, USBHSPHY_CTRL_REGOFFSET, 0xffff,
			  (0xfUL << USBHSPHY_TEST_ADD) |
			  (0xaaUL << USBHSPHY_TEST_DIN));

	regmap_write_bits(oxnas->syscon, USBHSPHY_CTRL_REGOFFSET, 0xffff,
			  (1UL << USBHSPHY_TEST_CLK) |
			  (0xfUL << USBHSPHY_TEST_ADD) |
			  (0xaaUL << USBHSPHY_TEST_DIN));

	if (oxnas->use_pllb) /* use pllb clock */
		regmap_write_bits(oxnas->syscon, USB_CTRL_REGOFFSET, 0xffff,
				  USB_CLK_INTERNAL | USB_INT_CLK_PLLB);
	else /* use ref300 derived clock */
		regmap_write_bits(oxnas->syscon, USB_CTRL_REGOFFSET, 0xffff,
				  USB_CLK_INTERNAL | USB_INT_CLK_REF300);

	if (oxnas->use_phya) {
		/* Configure USB PHYA as a host */
		regmap_update_bits(oxnas->syscon, USB_CTRL_REGOFFSET, USBAMUX_DEVICE, 0);
	}

	/* Enable the clock to the USB block */
	clk_prepare_enable(oxnas->clk);
}