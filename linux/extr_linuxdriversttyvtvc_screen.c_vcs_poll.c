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
struct vcs_poll_data {scalar_t__ seen_last_update; int /*<<< orphan*/  waitq; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int DEFAULT_POLLMASK ; 
 int EPOLLERR ; 
 int EPOLLPRI ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct vcs_poll_data* vcs_poll_data_get (struct file*) ; 

__attribute__((used)) static __poll_t
vcs_poll(struct file *file, poll_table *wait)
{
	struct vcs_poll_data *poll = vcs_poll_data_get(file);
	__poll_t ret = DEFAULT_POLLMASK|EPOLLERR|EPOLLPRI;

	if (poll) {
		poll_wait(file, &poll->waitq, wait);
		if (poll->seen_last_update)
			ret = DEFAULT_POLLMASK;
	}
	return ret;
}