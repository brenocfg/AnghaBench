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
struct socket {TYPE_1__* ops; int /*<<< orphan*/  sk; } ;
struct file {struct socket* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;
struct TYPE_2__ {int (* poll ) (struct file*,struct socket*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int POLL_BUSY_LOOP ; 
 int poll_requested_events (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_busy_loop (int /*<<< orphan*/ ,int) ; 
 scalar_t__ sk_can_busy_loop (int /*<<< orphan*/ ) ; 
 int stub1 (struct file*,struct socket*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t sock_poll(struct file *file, poll_table *wait)
{
	struct socket *sock = file->private_data;
	__poll_t events = poll_requested_events(wait), flag = 0;

	if (!sock->ops->poll)
		return 0;

	if (sk_can_busy_loop(sock->sk)) {
		/* poll once if requested by the syscall */
		if (events & POLL_BUSY_LOOP)
			sk_busy_loop(sock->sk, 1);

		/* if this socket can poll_ll, tell the system call */
		flag = POLL_BUSY_LOOP;
	}

	return sock->ops->poll(file, sock, wait) | flag;
}