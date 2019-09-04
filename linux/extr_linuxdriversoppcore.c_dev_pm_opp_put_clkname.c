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
struct opp_table {int /*<<< orphan*/  clk; int /*<<< orphan*/  opp_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_pm_opp_put_opp_table (struct opp_table*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

void dev_pm_opp_put_clkname(struct opp_table *opp_table)
{
	/* Make sure there are no concurrent readers while updating opp_table */
	WARN_ON(!list_empty(&opp_table->opp_list));

	clk_put(opp_table->clk);
	opp_table->clk = ERR_PTR(-EINVAL);

	dev_pm_opp_put_opp_table(opp_table);
}