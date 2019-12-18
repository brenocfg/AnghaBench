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
struct socket_wq {int /*<<< orphan*/  fasync_list; } ;
struct socket {struct socket_wq wq; struct sock* sk; } ;
struct sock {int dummy; } ;
struct file {struct socket* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SOCK_FASYNC ; 
 int /*<<< orphan*/  fasync_helper (int,struct file*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sock_reset_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sock_fasync(int fd, struct file *filp, int on)
{
	struct socket *sock = filp->private_data;
	struct sock *sk = sock->sk;
	struct socket_wq *wq = &sock->wq;

	if (sk == NULL)
		return -EINVAL;

	lock_sock(sk);
	fasync_helper(fd, filp, on, &wq->fasync_list);

	if (!wq->fasync_list)
		sock_reset_flag(sk, SOCK_FASYNC);
	else
		sock_set_flag(sk, SOCK_FASYNC);

	release_sock(sk);
	return 0;
}