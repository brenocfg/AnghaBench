#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  svm_port; int /*<<< orphan*/  svm_cid; } ;
struct vsock_sock {int ignore_connecting_rst; TYPE_5__ remote_addr; } ;
struct TYPE_9__ {int /*<<< orphan*/  context; } ;
struct TYPE_10__ {TYPE_3__ src; } ;
struct TYPE_8__ {int /*<<< orphan*/  size; int /*<<< orphan*/  handle; } ;
struct vmci_transport_packet {int type; int /*<<< orphan*/  src_port; TYPE_4__ dg; TYPE_2__ u; } ;
struct sock {int sk_err; int /*<<< orphan*/  (* sk_error_report ) (struct sock*) ;int /*<<< orphan*/  sk_state; int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;TYPE_1__* sk_socket; } ;
struct TYPE_12__ {int /*<<< orphan*/  detach_sub_id; int /*<<< orphan*/  consume_size; int /*<<< orphan*/  produce_size; int /*<<< orphan*/  qpair; int /*<<< orphan*/  qp_handle; } ;
struct TYPE_7__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int ECONNRESET ; 
 int EINVAL ; 
 int EPROTO ; 
 int /*<<< orphan*/  SS_CONNECTED ; 
 int /*<<< orphan*/  TCP_CLOSE ; 
 int /*<<< orphan*/  TCP_ESTABLISHED ; 
 int /*<<< orphan*/  VMCI_INVALID_ID ; 
#define  VMCI_TRANSPORT_PACKET_TYPE_ATTACH 132 
#define  VMCI_TRANSPORT_PACKET_TYPE_INVALID 131 
#define  VMCI_TRANSPORT_PACKET_TYPE_NEGOTIATE 130 
#define  VMCI_TRANSPORT_PACKET_TYPE_NEGOTIATE2 129 
#define  VMCI_TRANSPORT_PACKET_TYPE_RST 128 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  stub2 (struct sock*) ; 
 int /*<<< orphan*/  vmci_handle_is_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmci_handle_is_invalid (int /*<<< orphan*/ ) ; 
 TYPE_6__* vmci_trans (struct vsock_sock*) ; 
 int vmci_transport_recv_connecting_client_invalid (struct sock*,struct vmci_transport_packet*) ; 
 int vmci_transport_recv_connecting_client_negotiate (struct sock*,struct vmci_transport_packet*) ; 
 int /*<<< orphan*/  vmci_transport_send_reset (struct sock*,struct vmci_transport_packet*) ; 
 int /*<<< orphan*/  vsock_insert_connected (struct vsock_sock*) ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 

__attribute__((used)) static int
vmci_transport_recv_connecting_client(struct sock *sk,
				      struct vmci_transport_packet *pkt)
{
	struct vsock_sock *vsk;
	int err;
	int skerr;

	vsk = vsock_sk(sk);

	switch (pkt->type) {
	case VMCI_TRANSPORT_PACKET_TYPE_ATTACH:
		if (vmci_handle_is_invalid(pkt->u.handle) ||
		    !vmci_handle_is_equal(pkt->u.handle,
					  vmci_trans(vsk)->qp_handle)) {
			skerr = EPROTO;
			err = -EINVAL;
			goto destroy;
		}

		/* Signify the socket is connected and wakeup the waiter in
		 * connect(). Also place the socket in the connected table for
		 * accounting (it can already be found since it's in the bound
		 * table).
		 */
		sk->sk_state = TCP_ESTABLISHED;
		sk->sk_socket->state = SS_CONNECTED;
		vsock_insert_connected(vsk);
		sk->sk_state_change(sk);

		break;
	case VMCI_TRANSPORT_PACKET_TYPE_NEGOTIATE:
	case VMCI_TRANSPORT_PACKET_TYPE_NEGOTIATE2:
		if (pkt->u.size == 0
		    || pkt->dg.src.context != vsk->remote_addr.svm_cid
		    || pkt->src_port != vsk->remote_addr.svm_port
		    || !vmci_handle_is_invalid(vmci_trans(vsk)->qp_handle)
		    || vmci_trans(vsk)->qpair
		    || vmci_trans(vsk)->produce_size != 0
		    || vmci_trans(vsk)->consume_size != 0
		    || vmci_trans(vsk)->detach_sub_id != VMCI_INVALID_ID) {
			skerr = EPROTO;
			err = -EINVAL;

			goto destroy;
		}

		err = vmci_transport_recv_connecting_client_negotiate(sk, pkt);
		if (err) {
			skerr = -err;
			goto destroy;
		}

		break;
	case VMCI_TRANSPORT_PACKET_TYPE_INVALID:
		err = vmci_transport_recv_connecting_client_invalid(sk, pkt);
		if (err) {
			skerr = -err;
			goto destroy;
		}

		break;
	case VMCI_TRANSPORT_PACKET_TYPE_RST:
		/* Older versions of the linux code (WS 6.5 / ESX 4.0) used to
		 * continue processing here after they sent an INVALID packet.
		 * This meant that we got a RST after the INVALID. We ignore a
		 * RST after an INVALID. The common code doesn't send the RST
		 * ... so we can hang if an old version of the common code
		 * fails between getting a REQUEST and sending an OFFER back.
		 * Not much we can do about it... except hope that it doesn't
		 * happen.
		 */
		if (vsk->ignore_connecting_rst) {
			vsk->ignore_connecting_rst = false;
		} else {
			skerr = ECONNRESET;
			err = 0;
			goto destroy;
		}

		break;
	default:
		/* Close and cleanup the connection. */
		skerr = EPROTO;
		err = -EINVAL;
		goto destroy;
	}

	return 0;

destroy:
	vmci_transport_send_reset(sk, pkt);

	sk->sk_state = TCP_CLOSE;
	sk->sk_err = skerr;
	sk->sk_error_report(sk);
	return err;
}