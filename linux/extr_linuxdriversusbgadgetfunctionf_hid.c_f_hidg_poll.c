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
struct file {struct f_hidg* private_data; } ;
struct f_hidg {int /*<<< orphan*/  write_queue; int /*<<< orphan*/  read_queue; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 scalar_t__ READ_COND ; 
 scalar_t__ WRITE_COND ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t f_hidg_poll(struct file *file, poll_table *wait)
{
	struct f_hidg	*hidg  = file->private_data;
	__poll_t	ret = 0;

	poll_wait(file, &hidg->read_queue, wait);
	poll_wait(file, &hidg->write_queue, wait);

	if (WRITE_COND)
		ret |= EPOLLOUT | EPOLLWRNORM;

	if (READ_COND)
		ret |= EPOLLIN | EPOLLRDNORM;

	return ret;
}