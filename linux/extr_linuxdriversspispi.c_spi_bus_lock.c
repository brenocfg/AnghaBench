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
struct spi_controller {int bus_lock_flag; int /*<<< orphan*/  bus_lock_spinlock; int /*<<< orphan*/  bus_lock_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int spi_bus_lock(struct spi_controller *ctlr)
{
	unsigned long flags;

	mutex_lock(&ctlr->bus_lock_mutex);

	spin_lock_irqsave(&ctlr->bus_lock_spinlock, flags);
	ctlr->bus_lock_flag = 1;
	spin_unlock_irqrestore(&ctlr->bus_lock_spinlock, flags);

	/* mutex remains locked until spi_bus_unlock is called */

	return 0;
}