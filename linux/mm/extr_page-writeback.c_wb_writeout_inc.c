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
struct bdi_writeback {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __wb_writeout_inc (struct bdi_writeback*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

void wb_writeout_inc(struct bdi_writeback *wb)
{
	unsigned long flags;

	local_irq_save(flags);
	__wb_writeout_inc(wb);
	local_irq_restore(flags);
}