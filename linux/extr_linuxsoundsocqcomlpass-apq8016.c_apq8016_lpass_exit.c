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
struct platform_device {int dummy; } ;
struct lpass_data {int /*<<< orphan*/  pcnoc_sway_clk; int /*<<< orphan*/  pcnoc_mport_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct lpass_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int apq8016_lpass_exit(struct platform_device *pdev)
{
	struct lpass_data *drvdata = platform_get_drvdata(pdev);

	clk_disable_unprepare(drvdata->pcnoc_mport_clk);
	clk_disable_unprepare(drvdata->pcnoc_sway_clk);

	return 0;
}