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
typedef  int u32 ;
struct tegra_eqos {int /*<<< orphan*/  dev; int /*<<< orphan*/  clk_tx; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ AUTO_CAL_CONFIG ; 
 int AUTO_CAL_CONFIG_ENABLE ; 
 int AUTO_CAL_CONFIG_START ; 
 scalar_t__ AUTO_CAL_STATUS ; 
 int AUTO_CAL_STATUS_ACTIVE ; 
 scalar_t__ SDMEMCOMPPADCTRL ; 
 int SDMEMCOMPPADCTRL_PAD_E_INPUT_OR_E_PWRD ; 
#define  SPEED_10 130 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int readl (scalar_t__) ; 
 int readl_poll_timeout_atomic (scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void tegra_eqos_fix_speed(void *priv, unsigned int speed)
{
	struct tegra_eqos *eqos = priv;
	unsigned long rate = 125000000;
	bool needs_calibration = false;
	u32 value;
	int err;

	switch (speed) {
	case SPEED_1000:
		needs_calibration = true;
		rate = 125000000;
		break;

	case SPEED_100:
		needs_calibration = true;
		rate = 25000000;
		break;

	case SPEED_10:
		rate = 2500000;
		break;

	default:
		dev_err(eqos->dev, "invalid speed %u\n", speed);
		break;
	}

	if (needs_calibration) {
		/* calibrate */
		value = readl(eqos->regs + SDMEMCOMPPADCTRL);
		value |= SDMEMCOMPPADCTRL_PAD_E_INPUT_OR_E_PWRD;
		writel(value, eqos->regs + SDMEMCOMPPADCTRL);

		udelay(1);

		value = readl(eqos->regs + AUTO_CAL_CONFIG);
		value |= AUTO_CAL_CONFIG_START | AUTO_CAL_CONFIG_ENABLE;
		writel(value, eqos->regs + AUTO_CAL_CONFIG);

		err = readl_poll_timeout_atomic(eqos->regs + AUTO_CAL_STATUS,
						value,
						value & AUTO_CAL_STATUS_ACTIVE,
						1, 10);
		if (err < 0) {
			dev_err(eqos->dev, "calibration did not start\n");
			goto failed;
		}

		err = readl_poll_timeout_atomic(eqos->regs + AUTO_CAL_STATUS,
						value,
						(value & AUTO_CAL_STATUS_ACTIVE) == 0,
						20, 200);
		if (err < 0) {
			dev_err(eqos->dev, "calibration didn't finish\n");
			goto failed;
		}

	failed:
		value = readl(eqos->regs + SDMEMCOMPPADCTRL);
		value &= ~SDMEMCOMPPADCTRL_PAD_E_INPUT_OR_E_PWRD;
		writel(value, eqos->regs + SDMEMCOMPPADCTRL);
	} else {
		value = readl(eqos->regs + AUTO_CAL_CONFIG);
		value &= ~AUTO_CAL_CONFIG_ENABLE;
		writel(value, eqos->regs + AUTO_CAL_CONFIG);
	}

	err = clk_set_rate(eqos->clk_tx, rate);
	if (err < 0)
		dev_err(eqos->dev, "failed to set TX rate: %d\n", err);
}