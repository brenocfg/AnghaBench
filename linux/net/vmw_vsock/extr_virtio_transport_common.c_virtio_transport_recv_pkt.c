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
struct TYPE_4__ {int /*<<< orphan*/  svm_cid; } ;
struct vsock_sock {TYPE_2__ local_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  type; int /*<<< orphan*/  fwd_cnt; int /*<<< orphan*/  buf_alloc; int /*<<< orphan*/  flags; int /*<<< orphan*/  op; int /*<<< orphan*/  len; int /*<<< orphan*/  dst_port; int /*<<< orphan*/  dst_cid; int /*<<< orphan*/  src_port; int /*<<< orphan*/  src_cid; } ;
struct virtio_vsock_pkt {TYPE_1__ hdr; } ;
struct sockaddr_vm {int /*<<< orphan*/  svm_cid; int /*<<< orphan*/  svm_port; } ;
struct sock {int sk_state; int /*<<< orphan*/  (* sk_write_space ) (struct sock*) ;} ;

/* Variables and functions */
#define  TCP_CLOSING 131 
#define  TCP_ESTABLISHED 130 
#define  TCP_LISTEN 129 
#define  TCP_SYN_SENT 128 
 scalar_t__ VIRTIO_VSOCK_TYPE_STREAM ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  trace_virtio_transport_recv_pkt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_transport_free_pkt (struct virtio_vsock_pkt*) ; 
 int /*<<< orphan*/  virtio_transport_recv_connected (struct sock*,struct virtio_vsock_pkt*) ; 
 int /*<<< orphan*/  virtio_transport_recv_connecting (struct sock*,struct virtio_vsock_pkt*) ; 
 int /*<<< orphan*/  virtio_transport_recv_disconnecting (struct sock*,struct virtio_vsock_pkt*) ; 
 int /*<<< orphan*/  virtio_transport_recv_listen (struct sock*,struct virtio_vsock_pkt*) ; 
 int /*<<< orphan*/  virtio_transport_reset_no_sock (struct virtio_vsock_pkt*) ; 
 int virtio_transport_space_update (struct sock*,struct virtio_vsock_pkt*) ; 
 int /*<<< orphan*/  vsock_addr_init (struct sockaddr_vm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sock* vsock_find_bound_socket (struct sockaddr_vm*) ; 
 struct sock* vsock_find_connected_socket (struct sockaddr_vm*,struct sockaddr_vm*) ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 

void virtio_transport_recv_pkt(struct virtio_vsock_pkt *pkt)
{
	struct sockaddr_vm src, dst;
	struct vsock_sock *vsk;
	struct sock *sk;
	bool space_available;

	vsock_addr_init(&src, le64_to_cpu(pkt->hdr.src_cid),
			le32_to_cpu(pkt->hdr.src_port));
	vsock_addr_init(&dst, le64_to_cpu(pkt->hdr.dst_cid),
			le32_to_cpu(pkt->hdr.dst_port));

	trace_virtio_transport_recv_pkt(src.svm_cid, src.svm_port,
					dst.svm_cid, dst.svm_port,
					le32_to_cpu(pkt->hdr.len),
					le16_to_cpu(pkt->hdr.type),
					le16_to_cpu(pkt->hdr.op),
					le32_to_cpu(pkt->hdr.flags),
					le32_to_cpu(pkt->hdr.buf_alloc),
					le32_to_cpu(pkt->hdr.fwd_cnt));

	if (le16_to_cpu(pkt->hdr.type) != VIRTIO_VSOCK_TYPE_STREAM) {
		(void)virtio_transport_reset_no_sock(pkt);
		goto free_pkt;
	}

	/* The socket must be in connected or bound table
	 * otherwise send reset back
	 */
	sk = vsock_find_connected_socket(&src, &dst);
	if (!sk) {
		sk = vsock_find_bound_socket(&dst);
		if (!sk) {
			(void)virtio_transport_reset_no_sock(pkt);
			goto free_pkt;
		}
	}

	vsk = vsock_sk(sk);

	space_available = virtio_transport_space_update(sk, pkt);

	lock_sock(sk);

	/* Update CID in case it has changed after a transport reset event */
	vsk->local_addr.svm_cid = dst.svm_cid;

	if (space_available)
		sk->sk_write_space(sk);

	switch (sk->sk_state) {
	case TCP_LISTEN:
		virtio_transport_recv_listen(sk, pkt);
		virtio_transport_free_pkt(pkt);
		break;
	case TCP_SYN_SENT:
		virtio_transport_recv_connecting(sk, pkt);
		virtio_transport_free_pkt(pkt);
		break;
	case TCP_ESTABLISHED:
		virtio_transport_recv_connected(sk, pkt);
		break;
	case TCP_CLOSING:
		virtio_transport_recv_disconnecting(sk, pkt);
		virtio_transport_free_pkt(pkt);
		break;
	default:
		virtio_transport_free_pkt(pkt);
		break;
	}
	release_sock(sk);

	/* Release refcnt obtained when we fetched this socket out of the
	 * bound or connected list.
	 */
	sock_put(sk);
	return;

free_pkt:
	virtio_transport_free_pkt(pkt);
}