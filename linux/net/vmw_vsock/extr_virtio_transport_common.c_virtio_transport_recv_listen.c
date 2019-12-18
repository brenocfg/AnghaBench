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
struct vsock_sock {int /*<<< orphan*/  remote_addr; int /*<<< orphan*/  local_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  src_port; int /*<<< orphan*/  src_cid; int /*<<< orphan*/  dst_port; int /*<<< orphan*/  dst_cid; int /*<<< orphan*/  op; } ;
struct virtio_vsock_pkt {TYPE_1__ hdr; } ;
struct sock {int /*<<< orphan*/  (* sk_data_ready ) (struct sock*) ;int /*<<< orphan*/  sk_state; int /*<<< orphan*/  sk_ack_backlog; int /*<<< orphan*/  sk_type; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  TCP_ESTABLISHED ; 
 scalar_t__ VIRTIO_VSOCK_OP_REQUEST ; 
 struct sock* __vsock_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_sock_nested (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 scalar_t__ sk_acceptq_is_full (struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  virtio_transport_reset (struct vsock_sock*,struct virtio_vsock_pkt*) ; 
 int /*<<< orphan*/  virtio_transport_send_response (struct vsock_sock*,struct virtio_vsock_pkt*) ; 
 int /*<<< orphan*/  vsock_addr_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsock_enqueue_accept (struct sock*,struct sock*) ; 
 int /*<<< orphan*/  vsock_insert_connected (struct vsock_sock*) ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 

__attribute__((used)) static int
virtio_transport_recv_listen(struct sock *sk, struct virtio_vsock_pkt *pkt)
{
	struct vsock_sock *vsk = vsock_sk(sk);
	struct vsock_sock *vchild;
	struct sock *child;

	if (le16_to_cpu(pkt->hdr.op) != VIRTIO_VSOCK_OP_REQUEST) {
		virtio_transport_reset(vsk, pkt);
		return -EINVAL;
	}

	if (sk_acceptq_is_full(sk)) {
		virtio_transport_reset(vsk, pkt);
		return -ENOMEM;
	}

	child = __vsock_create(sock_net(sk), NULL, sk, GFP_KERNEL,
			       sk->sk_type, 0);
	if (!child) {
		virtio_transport_reset(vsk, pkt);
		return -ENOMEM;
	}

	sk->sk_ack_backlog++;

	lock_sock_nested(child, SINGLE_DEPTH_NESTING);

	child->sk_state = TCP_ESTABLISHED;

	vchild = vsock_sk(child);
	vsock_addr_init(&vchild->local_addr, le64_to_cpu(pkt->hdr.dst_cid),
			le32_to_cpu(pkt->hdr.dst_port));
	vsock_addr_init(&vchild->remote_addr, le64_to_cpu(pkt->hdr.src_cid),
			le32_to_cpu(pkt->hdr.src_port));

	vsock_insert_connected(vchild);
	vsock_enqueue_accept(sk, child);
	virtio_transport_send_response(vchild, pkt);

	release_sock(child);

	sk->sk_data_ready(sk);
	return 0;
}