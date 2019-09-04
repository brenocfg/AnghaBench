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
struct snd_timer_user {int /*<<< orphan*/  qlock; scalar_t__ disconnected; scalar_t__ qused; int /*<<< orphan*/  qchange_sleep; } ;
struct file {struct snd_timer_user* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t snd_timer_user_poll(struct file *file, poll_table * wait)
{
        __poll_t mask;
        struct snd_timer_user *tu;

        tu = file->private_data;

        poll_wait(file, &tu->qchange_sleep, wait);

	mask = 0;
	spin_lock_irq(&tu->qlock);
	if (tu->qused)
		mask |= EPOLLIN | EPOLLRDNORM;
	if (tu->disconnected)
		mask |= EPOLLERR;
	spin_unlock_irq(&tu->qlock);

	return mask;
}