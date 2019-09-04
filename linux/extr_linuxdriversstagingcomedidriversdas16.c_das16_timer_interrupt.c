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
struct timer_list {int dummy; } ;
struct das16_private_struct {int /*<<< orphan*/  timer; scalar_t__ timer_running; struct comedi_device* dev; } ;
struct comedi_device {int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  das16_interrupt (struct comedi_device*) ; 
 struct das16_private_struct* devpriv ; 
 struct das16_private_struct* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer ; 
 scalar_t__ timer_period () ; 

__attribute__((used)) static void das16_timer_interrupt(struct timer_list *t)
{
	struct das16_private_struct *devpriv = from_timer(devpriv, t, timer);
	struct comedi_device *dev = devpriv->dev;
	unsigned long flags;

	das16_interrupt(dev);

	spin_lock_irqsave(&dev->spinlock, flags);
	if (devpriv->timer_running)
		mod_timer(&devpriv->timer, jiffies + timer_period());
	spin_unlock_irqrestore(&dev->spinlock, flags);
}