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
struct slgt_info {int irq_requested; int reg_addr_requested; int /*<<< orphan*/ * reg_addr; int /*<<< orphan*/  phys_reg_addr; int /*<<< orphan*/  irq_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLGT_REG_SIZE ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct slgt_info*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void release_resources(struct slgt_info *info)
{
	if (info->irq_requested) {
		free_irq(info->irq_level, info);
		info->irq_requested = false;
	}

	if (info->reg_addr_requested) {
		release_mem_region(info->phys_reg_addr, SLGT_REG_SIZE);
		info->reg_addr_requested = false;
	}

	if (info->reg_addr) {
		iounmap(info->reg_addr);
		info->reg_addr = NULL;
	}
}