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
struct rchan_buf {int /*<<< orphan*/  read_wait; scalar_t__ finalized; } ;
struct file {int f_mode; struct rchan_buf* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int FMODE_READ ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  relay_buf_empty (struct rchan_buf*) ; 

__attribute__((used)) static __poll_t relay_file_poll(struct file *filp, poll_table *wait)
{
	__poll_t mask = 0;
	struct rchan_buf *buf = filp->private_data;

	if (buf->finalized)
		return EPOLLERR;

	if (filp->f_mode & FMODE_READ) {
		poll_wait(filp, &buf->read_wait, wait);
		if (!relay_buf_empty(buf))
			mask |= EPOLLIN | EPOLLRDNORM;
	}

	return mask;
}