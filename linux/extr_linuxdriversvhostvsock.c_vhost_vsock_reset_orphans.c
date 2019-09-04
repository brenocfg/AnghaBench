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
struct TYPE_2__ {int /*<<< orphan*/  svm_cid; } ;
struct vsock_sock {int /*<<< orphan*/  peer_shutdown; scalar_t__ close_work_scheduled; TYPE_1__ remote_addr; } ;
struct sock {int /*<<< orphan*/  (* sk_error_report ) (struct sock*) ;int /*<<< orphan*/  sk_err; int /*<<< orphan*/  sk_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECONNRESET ; 
 int /*<<< orphan*/  SHUTDOWN_MASK ; 
 int /*<<< orphan*/  SOCK_DONE ; 
 int /*<<< orphan*/  SS_UNCONNECTED ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 scalar_t__ vhost_vsock_get (int /*<<< orphan*/ ) ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 

__attribute__((used)) static void vhost_vsock_reset_orphans(struct sock *sk)
{
	struct vsock_sock *vsk = vsock_sk(sk);

	/* vmci_transport.c doesn't take sk_lock here either.  At least we're
	 * under vsock_table_lock so the sock cannot disappear while we're
	 * executing.
	 */

	/* If the peer is still valid, no need to reset connection */
	if (vhost_vsock_get(vsk->remote_addr.svm_cid))
		return;

	/* If the close timeout is pending, let it expire.  This avoids races
	 * with the timeout callback.
	 */
	if (vsk->close_work_scheduled)
		return;

	sock_set_flag(sk, SOCK_DONE);
	vsk->peer_shutdown = SHUTDOWN_MASK;
	sk->sk_state = SS_UNCONNECTED;
	sk->sk_err = ECONNRESET;
	sk->sk_error_report(sk);
}