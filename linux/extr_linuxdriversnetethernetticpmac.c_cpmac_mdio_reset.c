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
struct mii_bus {int /*<<< orphan*/  priv; int /*<<< orphan*/  dev; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR7_RESET_BIT_MDIO ; 
 int /*<<< orphan*/  CPMAC_MDIO_CONTROL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int MDIOC_CLKDIV (int) ; 
 int MDIOC_ENABLE ; 
 int /*<<< orphan*/  ar7_device_reset (int /*<<< orphan*/ ) ; 
 struct clk* clk_get (int /*<<< orphan*/ *,char*) ; 
 int clk_get_rate (struct clk*) ; 
 int /*<<< orphan*/  cpmac_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int cpmac_mdio_reset(struct mii_bus *bus)
{
	struct clk *cpmac_clk;

	cpmac_clk = clk_get(&bus->dev, "cpmac");
	if (IS_ERR(cpmac_clk)) {
		pr_err("unable to get cpmac clock\n");
		return -1;
	}
	ar7_device_reset(AR7_RESET_BIT_MDIO);
	cpmac_write(bus->priv, CPMAC_MDIO_CONTROL, MDIOC_ENABLE |
		    MDIOC_CLKDIV(clk_get_rate(cpmac_clk) / 2200000 - 1));

	return 0;
}