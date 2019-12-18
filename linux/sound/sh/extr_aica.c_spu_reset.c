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

/* Variables and functions */
 int /*<<< orphan*/  SPU_MEMORY_BASE ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  spu_disable () ; 
 int /*<<< orphan*/  spu_enable () ; 
 int /*<<< orphan*/  spu_memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void spu_reset(void)
{
	unsigned long flags;
	spu_disable();
	spu_memset(0, 0, 0x200000 / 4);
	/* Put ARM7 in endless loop */
	local_irq_save(flags);
	__raw_writel(0xea000002, SPU_MEMORY_BASE);
	local_irq_restore(flags);
	spu_enable();
}