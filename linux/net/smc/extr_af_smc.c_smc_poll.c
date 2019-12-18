#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct socket {struct sock* sk; } ;
struct sock {scalar_t__ sk_state; int sk_shutdown; TYPE_3__* sk_socket; scalar_t__ sk_err; } ;
struct TYPE_10__ {scalar_t__ urg_state; int /*<<< orphan*/  bytes_to_rcv; int /*<<< orphan*/  sndbuf_space; } ;
struct smc_sock {TYPE_4__ conn; TYPE_5__* clcsock; scalar_t__ use_fallback; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;
struct TYPE_11__ {TYPE_2__* sk; TYPE_1__* ops; } ;
struct TYPE_9__ {int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {scalar_t__ sk_err; } ;
struct TYPE_7__ {int (* poll ) (struct file*,TYPE_5__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLHUP ; 
 int EPOLLIN ; 
 int EPOLLNVAL ; 
 int EPOLLOUT ; 
 int EPOLLPRI ; 
 int EPOLLRDHUP ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 int RCV_SHUTDOWN ; 
 int SEND_SHUTDOWN ; 
 int SHUTDOWN_MASK ; 
 scalar_t__ SMC_APPCLOSEWAIT1 ; 
 scalar_t__ SMC_CLOSED ; 
 scalar_t__ SMC_INIT ; 
 scalar_t__ SMC_LISTEN ; 
 scalar_t__ SMC_URG_VALID ; 
 int /*<<< orphan*/  SOCKWQ_ASYNC_NOSPACE ; 
 int /*<<< orphan*/  SOCK_NOSPACE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_set_bit (int /*<<< orphan*/ ,struct sock*) ; 
 int smc_accept_poll (struct sock*) ; 
 struct smc_sock* smc_sk (struct sock*) ; 
 int /*<<< orphan*/  sock_poll_wait (struct file*,struct socket*,int /*<<< orphan*/ *) ; 
 int stub1 (struct file*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int stub2 (struct file*,TYPE_5__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t smc_poll(struct file *file, struct socket *sock,
			     poll_table *wait)
{
	struct sock *sk = sock->sk;
	struct smc_sock *smc;
	__poll_t mask = 0;

	if (!sk)
		return EPOLLNVAL;

	smc = smc_sk(sock->sk);
	if (smc->use_fallback) {
		/* delegate to CLC child sock */
		mask = smc->clcsock->ops->poll(file, smc->clcsock, wait);
		sk->sk_err = smc->clcsock->sk->sk_err;
	} else {
		if (sk->sk_state != SMC_CLOSED)
			sock_poll_wait(file, sock, wait);
		if (sk->sk_err)
			mask |= EPOLLERR;
		if ((sk->sk_shutdown == SHUTDOWN_MASK) ||
		    (sk->sk_state == SMC_CLOSED))
			mask |= EPOLLHUP;
		if (sk->sk_state == SMC_LISTEN) {
			/* woken up by sk_data_ready in smc_listen_work() */
			mask |= smc_accept_poll(sk);
		} else if (smc->use_fallback) { /* as result of connect_work()*/
			mask |= smc->clcsock->ops->poll(file, smc->clcsock,
							   wait);
			sk->sk_err = smc->clcsock->sk->sk_err;
		} else {
			if ((sk->sk_state != SMC_INIT &&
			     atomic_read(&smc->conn.sndbuf_space)) ||
			    sk->sk_shutdown & SEND_SHUTDOWN) {
				mask |= EPOLLOUT | EPOLLWRNORM;
			} else {
				sk_set_bit(SOCKWQ_ASYNC_NOSPACE, sk);
				set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
			}
			if (atomic_read(&smc->conn.bytes_to_rcv))
				mask |= EPOLLIN | EPOLLRDNORM;
			if (sk->sk_shutdown & RCV_SHUTDOWN)
				mask |= EPOLLIN | EPOLLRDNORM | EPOLLRDHUP;
			if (sk->sk_state == SMC_APPCLOSEWAIT1)
				mask |= EPOLLIN;
			if (smc->conn.urg_state == SMC_URG_VALID)
				mask |= EPOLLPRI;
		}
	}

	return mask;
}