#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct omap_mcbsp {int /*<<< orphan*/  fclk; int /*<<< orphan*/  pm_qos_req; int /*<<< orphan*/  id; TYPE_2__* pdata; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* free ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_mcbsp_cleanup (struct omap_mcbsp*) ; 
 struct omap_mcbsp* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_qos_remove_request (int /*<<< orphan*/ *) ; 
 scalar_t__ pm_qos_request_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asoc_mcbsp_remove(struct platform_device *pdev)
{
	struct omap_mcbsp *mcbsp = platform_get_drvdata(pdev);

	if (mcbsp->pdata->ops && mcbsp->pdata->ops->free)
		mcbsp->pdata->ops->free(mcbsp->id);

	if (pm_qos_request_active(&mcbsp->pm_qos_req))
		pm_qos_remove_request(&mcbsp->pm_qos_req);

	omap_mcbsp_cleanup(mcbsp);

	clk_put(mcbsp->fclk);

	return 0;
}