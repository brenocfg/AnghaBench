#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vsock_sock {int /*<<< orphan*/  peer_shutdown; } ;
struct TYPE_4__ {int /*<<< orphan*/  mode; } ;
struct vmci_transport_packet {int type; TYPE_1__ u; } ;
struct sock {int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;int /*<<< orphan*/  sk_state; } ;
struct TYPE_6__ {TYPE_2__* notify_ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* handle_notify_pkt ) (struct sock*,struct vmci_transport_packet*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SHUTDOWN_MASK ; 
 int /*<<< orphan*/  SOCK_DONE ; 
 int /*<<< orphan*/  TCP_CLOSING ; 
#define  VMCI_TRANSPORT_PACKET_TYPE_RST 129 
#define  VMCI_TRANSPORT_PACKET_TYPE_SHUTDOWN 128 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  stub2 (struct sock*) ; 
 int /*<<< orphan*/  stub3 (struct sock*,struct vmci_transport_packet*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 TYPE_3__* vmci_trans (struct vsock_sock*) ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 
 int /*<<< orphan*/  vsock_stream_has_data (struct vsock_sock*) ; 

__attribute__((used)) static int vmci_transport_recv_connected(struct sock *sk,
					 struct vmci_transport_packet *pkt)
{
	struct vsock_sock *vsk;
	bool pkt_processed = false;

	/* In cases where we are closing the connection, it's sufficient to
	 * mark the state change (and maybe error) and wake up any waiting
	 * threads. Since this is a connected socket, it's owned by a user
	 * process and will be cleaned up when the failure is passed back on
	 * the current or next system call.  Our system call implementations
	 * must therefore check for error and state changes on entry and when
	 * being awoken.
	 */
	switch (pkt->type) {
	case VMCI_TRANSPORT_PACKET_TYPE_SHUTDOWN:
		if (pkt->u.mode) {
			vsk = vsock_sk(sk);

			vsk->peer_shutdown |= pkt->u.mode;
			sk->sk_state_change(sk);
		}
		break;

	case VMCI_TRANSPORT_PACKET_TYPE_RST:
		vsk = vsock_sk(sk);
		/* It is possible that we sent our peer a message (e.g a
		 * WAITING_READ) right before we got notified that the peer had
		 * detached. If that happens then we can get a RST pkt back
		 * from our peer even though there is data available for us to
		 * read. In that case, don't shutdown the socket completely but
		 * instead allow the local client to finish reading data off
		 * the queuepair. Always treat a RST pkt in connected mode like
		 * a clean shutdown.
		 */
		sock_set_flag(sk, SOCK_DONE);
		vsk->peer_shutdown = SHUTDOWN_MASK;
		if (vsock_stream_has_data(vsk) <= 0)
			sk->sk_state = TCP_CLOSING;

		sk->sk_state_change(sk);
		break;

	default:
		vsk = vsock_sk(sk);
		vmci_trans(vsk)->notify_ops->handle_notify_pkt(
				sk, pkt, false, NULL, NULL,
				&pkt_processed);
		if (!pkt_processed)
			return -EINVAL;

		break;
	}

	return 0;
}