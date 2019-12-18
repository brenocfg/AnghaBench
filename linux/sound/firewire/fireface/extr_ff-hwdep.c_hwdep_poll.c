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
struct snd_hwdep {struct snd_ff* private_data; } ;
struct snd_ff {int /*<<< orphan*/  lock; scalar_t__ dev_lock_changed; int /*<<< orphan*/  hwdep_wait; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t hwdep_poll(struct snd_hwdep *hwdep, struct file *file,
			       poll_table *wait)
{
	struct snd_ff *ff = hwdep->private_data;
	__poll_t events;

	poll_wait(file, &ff->hwdep_wait, wait);

	spin_lock_irq(&ff->lock);
	if (ff->dev_lock_changed)
		events = EPOLLIN | EPOLLRDNORM;
	else
		events = 0;
	spin_unlock_irq(&ff->lock);

	return events;
}