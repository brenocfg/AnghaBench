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
struct reset_controller_dev {int dummy; } ;
struct imx7_src_signal {unsigned int bit; int /*<<< orphan*/  offset; } ;
struct imx7_src {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
#define  IMX7_RESET_PCIEPHY 129 
#define  IMX7_RESET_PCIE_CTRL_APPS_EN 128 
 struct imx7_src_signal* imx7_src_signals ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct imx7_src* to_imx7_src (struct reset_controller_dev*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int imx7_reset_set(struct reset_controller_dev *rcdev,
			  unsigned long id, bool assert)
{
	struct imx7_src *imx7src = to_imx7_src(rcdev);
	const struct imx7_src_signal *signal = &imx7_src_signals[id];
	unsigned int value = assert ? signal->bit : 0;

	switch (id) {
	case IMX7_RESET_PCIEPHY:
		/*
		 * wait for more than 10us to release phy g_rst and
		 * btnrst
		 */
		if (!assert)
			udelay(10);
		break;

	case IMX7_RESET_PCIE_CTRL_APPS_EN:
		value = (assert) ? 0 : signal->bit;
		break;
	}

	return regmap_update_bits(imx7src->regmap,
				  signal->offset, signal->bit, value);
}