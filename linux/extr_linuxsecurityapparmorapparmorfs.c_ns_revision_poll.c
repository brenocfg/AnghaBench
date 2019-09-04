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
struct file {struct aa_revision* private_data; } ;
struct aa_revision {scalar_t__ last_read; TYPE_1__* ns; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;
struct TYPE_2__ {scalar_t__ revision; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait; int /*<<< orphan*/  level; } ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t ns_revision_poll(struct file *file, poll_table *pt)
{
	struct aa_revision *rev = file->private_data;
	__poll_t mask = 0;

	if (rev) {
		mutex_lock_nested(&rev->ns->lock, rev->ns->level);
		poll_wait(file, &rev->ns->wait, pt);
		if (rev->last_read < rev->ns->revision)
			mask |= EPOLLIN | EPOLLRDNORM;
		mutex_unlock(&rev->ns->lock);
	}

	return mask;
}