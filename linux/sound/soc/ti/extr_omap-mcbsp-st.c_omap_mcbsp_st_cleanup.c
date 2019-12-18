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
struct omap_mcbsp {TYPE_2__* st_data; TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  mcbsp_iclk; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 struct omap_mcbsp* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sidetone_attr_group ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void omap_mcbsp_st_cleanup(struct platform_device *pdev)
{
	struct omap_mcbsp *mcbsp = platform_get_drvdata(pdev);

	if (mcbsp->st_data) {
		sysfs_remove_group(&mcbsp->dev->kobj, &sidetone_attr_group);
		clk_put(mcbsp->st_data->mcbsp_iclk);
	}
}