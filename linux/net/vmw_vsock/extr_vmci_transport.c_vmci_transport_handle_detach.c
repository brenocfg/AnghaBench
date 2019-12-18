#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ svm_cid; } ;
struct vsock_sock {TYPE_1__ local_addr; int /*<<< orphan*/  peer_shutdown; } ;
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;int /*<<< orphan*/  (* sk_error_report ) (struct sock*) ;int /*<<< orphan*/  sk_err; } ;
struct TYPE_4__ {int /*<<< orphan*/  qp_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECONNRESET ; 
 int /*<<< orphan*/  SHUTDOWN_MASK ; 
 int /*<<< orphan*/  SOCK_DONE ; 
 void* TCP_CLOSE ; 
 scalar_t__ TCP_SYN_SENT ; 
 scalar_t__ VMADDR_CID_HOST ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  stub2 (struct sock*) ; 
 int /*<<< orphan*/  vmci_handle_is_invalid (int /*<<< orphan*/ ) ; 
 TYPE_2__* vmci_trans (struct vsock_sock*) ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 
 scalar_t__ vsock_stream_has_data (struct vsock_sock*) ; 

__attribute__((used)) static void vmci_transport_handle_detach(struct sock *sk)
{
	struct vsock_sock *vsk;

	vsk = vsock_sk(sk);
	if (!vmci_handle_is_invalid(vmci_trans(vsk)->qp_handle)) {
		sock_set_flag(sk, SOCK_DONE);

		/* On a detach the peer will not be sending or receiving
		 * anymore.
		 */
		vsk->peer_shutdown = SHUTDOWN_MASK;

		/* We should not be sending anymore since the peer won't be
		 * there to receive, but we can still receive if there is data
		 * left in our consume queue. If the local endpoint is a host,
		 * we can't call vsock_stream_has_data, since that may block,
		 * but a host endpoint can't read data once the VM has
		 * detached, so there is no available data in that case.
		 */
		if (vsk->local_addr.svm_cid == VMADDR_CID_HOST ||
		    vsock_stream_has_data(vsk) <= 0) {
			if (sk->sk_state == TCP_SYN_SENT) {
				/* The peer may detach from a queue pair while
				 * we are still in the connecting state, i.e.,
				 * if the peer VM is killed after attaching to
				 * a queue pair, but before we complete the
				 * handshake. In that case, we treat the detach
				 * event like a reset.
				 */

				sk->sk_state = TCP_CLOSE;
				sk->sk_err = ECONNRESET;
				sk->sk_error_report(sk);
				return;
			}
			sk->sk_state = TCP_CLOSE;
		}
		sk->sk_state_change(sk);
	}
}