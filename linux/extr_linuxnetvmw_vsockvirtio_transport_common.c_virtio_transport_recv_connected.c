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
struct vsock_sock {int /*<<< orphan*/  peer_shutdown; struct virtio_vsock_sock* trans; } ;
struct virtio_vsock_sock {int /*<<< orphan*/  rx_lock; int /*<<< orphan*/  rx_queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  len; int /*<<< orphan*/  op; } ;
struct virtio_vsock_pkt {int len; TYPE_1__ hdr; int /*<<< orphan*/  list; int /*<<< orphan*/  off; } ;
struct sock {int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;int /*<<< orphan*/  sk_state; int /*<<< orphan*/  (* sk_write_space ) (struct sock*) ;int /*<<< orphan*/  (* sk_data_ready ) (struct sock*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RCV_SHUTDOWN ; 
 int /*<<< orphan*/  SEND_SHUTDOWN ; 
 int /*<<< orphan*/  SHUTDOWN_MASK ; 
 int /*<<< orphan*/  TCP_CLOSING ; 
#define  VIRTIO_VSOCK_OP_CREDIT_UPDATE 131 
#define  VIRTIO_VSOCK_OP_RST 130 
#define  VIRTIO_VSOCK_OP_RW 129 
#define  VIRTIO_VSOCK_OP_SHUTDOWN 128 
 int VIRTIO_VSOCK_SHUTDOWN_RCV ; 
 int VIRTIO_VSOCK_SHUTDOWN_SEND ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  stub2 (struct sock*) ; 
 int /*<<< orphan*/  stub3 (struct sock*) ; 
 int /*<<< orphan*/  virtio_transport_do_close (struct vsock_sock*,int) ; 
 int /*<<< orphan*/  virtio_transport_free_pkt (struct virtio_vsock_pkt*) ; 
 int /*<<< orphan*/  virtio_transport_inc_rx_pkt (struct virtio_vsock_sock*,struct virtio_vsock_pkt*) ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 
 int /*<<< orphan*/  vsock_stream_has_data (struct vsock_sock*) ; 

__attribute__((used)) static int
virtio_transport_recv_connected(struct sock *sk,
				struct virtio_vsock_pkt *pkt)
{
	struct vsock_sock *vsk = vsock_sk(sk);
	struct virtio_vsock_sock *vvs = vsk->trans;
	int err = 0;

	switch (le16_to_cpu(pkt->hdr.op)) {
	case VIRTIO_VSOCK_OP_RW:
		pkt->len = le32_to_cpu(pkt->hdr.len);
		pkt->off = 0;

		spin_lock_bh(&vvs->rx_lock);
		virtio_transport_inc_rx_pkt(vvs, pkt);
		list_add_tail(&pkt->list, &vvs->rx_queue);
		spin_unlock_bh(&vvs->rx_lock);

		sk->sk_data_ready(sk);
		return err;
	case VIRTIO_VSOCK_OP_CREDIT_UPDATE:
		sk->sk_write_space(sk);
		break;
	case VIRTIO_VSOCK_OP_SHUTDOWN:
		if (le32_to_cpu(pkt->hdr.flags) & VIRTIO_VSOCK_SHUTDOWN_RCV)
			vsk->peer_shutdown |= RCV_SHUTDOWN;
		if (le32_to_cpu(pkt->hdr.flags) & VIRTIO_VSOCK_SHUTDOWN_SEND)
			vsk->peer_shutdown |= SEND_SHUTDOWN;
		if (vsk->peer_shutdown == SHUTDOWN_MASK &&
		    vsock_stream_has_data(vsk) <= 0)
			sk->sk_state = TCP_CLOSING;
		if (le32_to_cpu(pkt->hdr.flags))
			sk->sk_state_change(sk);
		break;
	case VIRTIO_VSOCK_OP_RST:
		virtio_transport_do_close(vsk, true);
		break;
	default:
		err = -EINVAL;
		break;
	}

	virtio_transport_free_pkt(pkt);
	return err;
}