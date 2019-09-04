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
struct kirin_pcie {int /*<<< orphan*/  gpio_id_reset; int /*<<< orphan*/  sysctrl; int /*<<< orphan*/  crgctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRGCTRL_PCIE_ASSERT_BIT ; 
 int /*<<< orphan*/  CRGCTRL_PCIE_ASSERT_OFFSET ; 
 int /*<<< orphan*/  PERST_2_ACCESS_MAX ; 
 int /*<<< orphan*/  PERST_2_ACCESS_MIN ; 
 int /*<<< orphan*/  REF_2_PERST_MAX ; 
 int /*<<< orphan*/  REF_2_PERST_MIN ; 
 int /*<<< orphan*/  SCTRL_PCIE_CMOS_BIT ; 
 int /*<<< orphan*/  SCTRL_PCIE_CMOS_OFFSET ; 
 int /*<<< orphan*/  SCTRL_PCIE_HPCLK_BIT ; 
 int /*<<< orphan*/  SCTRL_PCIE_HPCLK_OFFSET ; 
 int /*<<< orphan*/  SCTRL_PCIE_ISO_BIT ; 
 int /*<<< orphan*/  SCTRL_PCIE_ISO_OFFSET ; 
 int /*<<< orphan*/  TIME_CMOS_MAX ; 
 int /*<<< orphan*/  TIME_CMOS_MIN ; 
 int gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_request (int /*<<< orphan*/ ,char*) ; 
 int kirin_pcie_clk_ctrl (struct kirin_pcie*,int) ; 
 int /*<<< orphan*/  kirin_pcie_oe_enable (struct kirin_pcie*) ; 
 int kirin_pcie_phy_init (struct kirin_pcie*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kirin_pcie_power_on(struct kirin_pcie *kirin_pcie)
{
	int ret;

	/* Power supply for Host */
	regmap_write(kirin_pcie->sysctrl,
		     SCTRL_PCIE_CMOS_OFFSET, SCTRL_PCIE_CMOS_BIT);
	usleep_range(TIME_CMOS_MIN, TIME_CMOS_MAX);
	kirin_pcie_oe_enable(kirin_pcie);

	ret = kirin_pcie_clk_ctrl(kirin_pcie, true);
	if (ret)
		return ret;

	/* ISO disable, PCIeCtrl, PHY assert and clk gate clear */
	regmap_write(kirin_pcie->sysctrl,
		     SCTRL_PCIE_ISO_OFFSET, SCTRL_PCIE_ISO_BIT);
	regmap_write(kirin_pcie->crgctrl,
		     CRGCTRL_PCIE_ASSERT_OFFSET, CRGCTRL_PCIE_ASSERT_BIT);
	regmap_write(kirin_pcie->sysctrl,
		     SCTRL_PCIE_HPCLK_OFFSET, SCTRL_PCIE_HPCLK_BIT);

	ret = kirin_pcie_phy_init(kirin_pcie);
	if (ret)
		goto close_clk;

	/* perst assert Endpoint */
	if (!gpio_request(kirin_pcie->gpio_id_reset, "pcie_perst")) {
		usleep_range(REF_2_PERST_MIN, REF_2_PERST_MAX);
		ret = gpio_direction_output(kirin_pcie->gpio_id_reset, 1);
		if (ret)
			goto close_clk;
		usleep_range(PERST_2_ACCESS_MIN, PERST_2_ACCESS_MAX);

		return 0;
	}

close_clk:
	kirin_pcie_clk_ctrl(kirin_pcie, false);
	return ret;
}