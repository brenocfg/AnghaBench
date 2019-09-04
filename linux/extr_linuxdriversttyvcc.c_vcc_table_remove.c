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
 unsigned long VCC_MAX_PORTS ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ ** vcc_table ; 
 int /*<<< orphan*/  vcc_table_lock ; 

__attribute__((used)) static void vcc_table_remove(unsigned long index)
{
	unsigned long flags;

	if (WARN_ON(index >= VCC_MAX_PORTS))
		return;

	spin_lock_irqsave(&vcc_table_lock, flags);
	vcc_table[index] = NULL;
	spin_unlock_irqrestore(&vcc_table_lock, flags);
}