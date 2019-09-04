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
struct snd_motu {int /*<<< orphan*/  lock; scalar_t__ msg; scalar_t__ dev_lock_changed; int /*<<< orphan*/  hwdep_wait; } ;
struct snd_hwdep {struct snd_motu* private_data; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t hwdep_poll(struct snd_hwdep *hwdep, struct file *file,
			       poll_table *wait)
{
	struct snd_motu *motu = hwdep->private_data;
	__poll_t events;

	poll_wait(file, &motu->hwdep_wait, wait);

	spin_lock_irq(&motu->lock);
	if (motu->dev_lock_changed || motu->msg)
		events = EPOLLIN | EPOLLRDNORM;
	else
		events = 0;
	spin_unlock_irq(&motu->lock);

	return events | EPOLLOUT;
}