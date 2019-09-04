#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct w1_master {TYPE_1__* bus_master; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* write_bit ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  w1_delay (int) ; 
 scalar_t__ w1_disable_irqs ; 

__attribute__((used)) static void w1_write_bit(struct w1_master *dev, int bit)
{
	unsigned long flags = 0;

	if(w1_disable_irqs) local_irq_save(flags);

	if (bit) {
		dev->bus_master->write_bit(dev->bus_master->data, 0);
		w1_delay(6);
		dev->bus_master->write_bit(dev->bus_master->data, 1);
		w1_delay(64);
	} else {
		dev->bus_master->write_bit(dev->bus_master->data, 0);
		w1_delay(60);
		dev->bus_master->write_bit(dev->bus_master->data, 1);
		w1_delay(10);
	}

	if(w1_disable_irqs) local_irq_restore(flags);
}