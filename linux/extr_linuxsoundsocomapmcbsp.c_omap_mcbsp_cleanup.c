#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct omap_mcbsp {TYPE_3__* st_data; TYPE_2__* dev; TYPE_1__* pdata; } ;
struct TYPE_6__ {int /*<<< orphan*/  mcbsp_iclk; } ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {scalar_t__ buffer_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  additional_attr_group ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sidetone_attr_group ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void omap_mcbsp_cleanup(struct omap_mcbsp *mcbsp)
{
	if (mcbsp->pdata->buffer_size)
		sysfs_remove_group(&mcbsp->dev->kobj, &additional_attr_group);

	if (mcbsp->st_data) {
		sysfs_remove_group(&mcbsp->dev->kobj, &sidetone_attr_group);
		clk_put(mcbsp->st_data->mcbsp_iclk);
	}
}