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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int AICA_CMD_KICK ; 
 int AICA_CMD_START ; 
 scalar_t__ AICA_CONTROL_POINT ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  spu_write_wait () ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void aica_chn_start(void)
{
	unsigned long flags;
	spu_write_wait();
	local_irq_save(flags);
	writel(AICA_CMD_KICK | AICA_CMD_START, (u32 *) AICA_CONTROL_POINT);
	local_irq_restore(flags);
}