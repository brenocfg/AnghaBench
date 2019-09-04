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
struct emac_adapter {int /*<<< orphan*/ * clk; } ;

/* Variables and functions */
 unsigned int EMAC_CLK_CNT ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void emac_clks_teardown(struct emac_adapter *adpt)
{

	unsigned int i;

	for (i = 0; i < EMAC_CLK_CNT; i++)
		clk_disable_unprepare(adpt->clk[i]);
}