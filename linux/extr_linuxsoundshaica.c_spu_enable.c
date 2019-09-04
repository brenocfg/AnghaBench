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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_RESET_REGISTER ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spu_write_wait () ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spu_enable(void)
{
	unsigned long flags;
	u32 regval = readl(ARM_RESET_REGISTER);
	regval &= ~1;
	spu_write_wait();
	local_irq_save(flags);
	writel(regval, ARM_RESET_REGISTER);
	local_irq_restore(flags);
}