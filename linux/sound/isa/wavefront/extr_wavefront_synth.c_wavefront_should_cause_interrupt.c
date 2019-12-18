#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wait_queue_entry_t ;
struct TYPE_3__ {scalar_t__ irq_ok; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  interrupt_sleeper; } ;
typedef  TYPE_1__ snd_wavefront_t ;

/* Variables and functions */
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  init_waitqueue_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void
wavefront_should_cause_interrupt (snd_wavefront_t *dev, 
				  int val, int port, unsigned long timeout)

{
	wait_queue_entry_t wait;

	init_waitqueue_entry(&wait, current);
	spin_lock_irq(&dev->irq_lock);
	add_wait_queue(&dev->interrupt_sleeper, &wait);
	dev->irq_ok = 0;
	outb (val,port);
	spin_unlock_irq(&dev->irq_lock);
	while (!dev->irq_ok && time_before(jiffies, timeout)) {
		schedule_timeout_uninterruptible(1);
		barrier();
	}
}