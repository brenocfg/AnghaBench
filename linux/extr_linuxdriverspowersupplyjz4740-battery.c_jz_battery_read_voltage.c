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
struct jz_battery {int /*<<< orphan*/  lock; int /*<<< orphan*/  irq; int /*<<< orphan*/  pdev; TYPE_3__* cell; TYPE_2__* pdata; int /*<<< orphan*/  base; int /*<<< orphan*/  read_completion; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* disable ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* enable ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int voltage_max_design; } ;
struct TYPE_5__ {TYPE_1__ info; } ;

/* Variables and functions */
 long ETIMEDOUT ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 long wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long jz_battery_read_voltage(struct jz_battery *battery)
{
	long t;
	unsigned long val;
	long voltage;

	mutex_lock(&battery->lock);

	reinit_completion(&battery->read_completion);

	enable_irq(battery->irq);
	battery->cell->enable(battery->pdev);

	t = wait_for_completion_interruptible_timeout(&battery->read_completion,
		HZ);

	if (t > 0) {
		val = readw(battery->base) & 0xfff;

		if (battery->pdata->info.voltage_max_design <= 2500000)
			val = (val * 78125UL) >> 7UL;
		else
			val = ((val * 924375UL) >> 9UL) + 33000;
		voltage = (long)val;
	} else {
		voltage = t ? t : -ETIMEDOUT;
	}

	battery->cell->disable(battery->pdev);
	disable_irq(battery->irq);

	mutex_unlock(&battery->lock);

	return voltage;
}