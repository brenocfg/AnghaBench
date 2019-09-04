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
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  megasas_poll_wait ; 
 scalar_t__ megasas_poll_wait_aen ; 
 int /*<<< orphan*/  poll_aen_lock ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static __poll_t megasas_mgmt_poll(struct file *file, poll_table *wait)
{
	__poll_t mask;
	unsigned long flags;

	poll_wait(file, &megasas_poll_wait, wait);
	spin_lock_irqsave(&poll_aen_lock, flags);
	if (megasas_poll_wait_aen)
		mask = (EPOLLIN | EPOLLRDNORM);
	else
		mask = 0;
	megasas_poll_wait_aen = 0;
	spin_unlock_irqrestore(&poll_aen_lock, flags);
	return mask;
}