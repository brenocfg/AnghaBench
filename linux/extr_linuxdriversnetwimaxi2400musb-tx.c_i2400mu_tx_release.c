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
struct task_struct {int dummy; } ;
struct i2400m {int /*<<< orphan*/  tx_lock; } ;
struct i2400mu {struct task_struct* tx_kthread; struct i2400m i2400m; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_printf (int,struct device*,char*) ; 
 struct device* i2400m_dev (struct i2400m*) ; 
 int /*<<< orphan*/  kthread_stop (struct task_struct*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void i2400mu_tx_release(struct i2400mu *i2400mu)
{
	unsigned long flags;
	struct i2400m *i2400m = &i2400mu->i2400m;
	struct device *dev = i2400m_dev(i2400m);
	struct task_struct *kthread;

	spin_lock_irqsave(&i2400m->tx_lock, flags);
	kthread = i2400mu->tx_kthread;
	i2400mu->tx_kthread = NULL;
	spin_unlock_irqrestore(&i2400m->tx_lock, flags);
	if (kthread)
		kthread_stop(kthread);
	else
		d_printf(1, dev, "TX: kthread had already exited\n");
}