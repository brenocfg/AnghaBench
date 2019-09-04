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
struct ti_pipe3 {int sata_refclk_enabled; int /*<<< orphan*/  div_clk; int /*<<< orphan*/  refclk; int /*<<< orphan*/  wkupclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ti_pipe3_disable_clocks(struct ti_pipe3 *phy)
{
	if (!IS_ERR(phy->wkupclk))
		clk_disable_unprepare(phy->wkupclk);
	if (!IS_ERR(phy->refclk)) {
		clk_disable_unprepare(phy->refclk);
		/*
		 * SATA refclk needs an additional disable as we left it
		 * on in probe to avoid Errata i783
		 */
		if (phy->sata_refclk_enabled) {
			clk_disable_unprepare(phy->refclk);
			phy->sata_refclk_enabled = false;
		}
	}

	if (!IS_ERR(phy->div_clk))
		clk_disable_unprepare(phy->div_clk);
}