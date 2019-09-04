#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rpc_xprt {int dummy; } ;
struct sock_xprt {int /*<<< orphan*/  recv_mutex; int /*<<< orphan*/  recv_worker; int /*<<< orphan*/  sock_state; struct sock* inet; struct rpc_xprt xprt; } ;
struct sock {int dummy; } ;
struct TYPE_4__ {struct rpc_xprt* data; } ;
struct TYPE_5__ {scalar_t__ count; TYPE_1__ arg; } ;
typedef  TYPE_2__ read_descriptor_t ;

/* Variables and functions */
 scalar_t__ RPC_TCP_READ_CHUNK_SZ ; 
 int /*<<< orphan*/  XPRT_SOCK_DATA_READY ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ need_resched () ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int tcp_read_sock (struct sock*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xs_tcp_data_ready (struct rpc_xprt*,int,unsigned long) ; 
 int /*<<< orphan*/  xprtiod_workqueue ; 
 int /*<<< orphan*/  xs_tcp_data_recv ; 

__attribute__((used)) static void xs_tcp_data_receive(struct sock_xprt *transport)
{
	struct rpc_xprt *xprt = &transport->xprt;
	struct sock *sk;
	read_descriptor_t rd_desc = {
		.arg.data = xprt,
	};
	unsigned long total = 0;
	int read = 0;

restart:
	mutex_lock(&transport->recv_mutex);
	sk = transport->inet;
	if (sk == NULL)
		goto out;

	/* We use rd_desc to pass struct xprt to xs_tcp_data_recv */
	for (;;) {
		rd_desc.count = RPC_TCP_READ_CHUNK_SZ;
		lock_sock(sk);
		read = tcp_read_sock(sk, &rd_desc, xs_tcp_data_recv);
		if (rd_desc.count != 0 || read < 0) {
			clear_bit(XPRT_SOCK_DATA_READY, &transport->sock_state);
			release_sock(sk);
			break;
		}
		release_sock(sk);
		total += read;
		if (need_resched()) {
			mutex_unlock(&transport->recv_mutex);
			cond_resched();
			goto restart;
		}
	}
	if (test_bit(XPRT_SOCK_DATA_READY, &transport->sock_state))
		queue_work(xprtiod_workqueue, &transport->recv_worker);
out:
	mutex_unlock(&transport->recv_mutex);
	trace_xs_tcp_data_ready(xprt, read, total);
}