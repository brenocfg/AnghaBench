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
struct smo8800_device {int /*<<< orphan*/  misc_wait; int /*<<< orphan*/  counter; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t smo8800_interrupt_quick(int irq, void *data)
{
	struct smo8800_device *smo8800 = data;

	atomic_inc(&smo8800->counter);
	wake_up_interruptible(&smo8800->misc_wait);
	return IRQ_WAKE_THREAD;
}