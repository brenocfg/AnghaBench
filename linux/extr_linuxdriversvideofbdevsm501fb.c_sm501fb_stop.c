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
struct sm501fb_info {TYPE_2__* regs_res; int /*<<< orphan*/  regs; TYPE_2__* regs2d_res; int /*<<< orphan*/  regs2d; TYPE_2__* fbmem_res; int /*<<< orphan*/  fbmem; TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  start; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  SM501_GATE_DISPLAY ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (TYPE_2__*) ; 
 int /*<<< orphan*/  sm501_unit_power (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sm501fb_stop(struct sm501fb_info *info)
{
	/* disable display controller */
	sm501_unit_power(info->dev->parent, SM501_GATE_DISPLAY, 0);

	iounmap(info->fbmem);
	release_mem_region(info->fbmem_res->start,
			   resource_size(info->fbmem_res));

	iounmap(info->regs2d);
	release_mem_region(info->regs2d_res->start,
			   resource_size(info->regs2d_res));

	iounmap(info->regs);
	release_mem_region(info->regs_res->start,
			   resource_size(info->regs_res));
}