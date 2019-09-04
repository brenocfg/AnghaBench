#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct lpass_data {int /*<<< orphan*/  ahbix_clk; TYPE_1__* variant; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* exit ) (struct platform_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct lpass_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stub1 (struct platform_device*) ; 

int asoc_qcom_lpass_cpu_platform_remove(struct platform_device *pdev)
{
	struct lpass_data *drvdata = platform_get_drvdata(pdev);

	if (drvdata->variant->exit)
		drvdata->variant->exit(pdev);

	clk_disable_unprepare(drvdata->ahbix_clk);

	return 0;
}