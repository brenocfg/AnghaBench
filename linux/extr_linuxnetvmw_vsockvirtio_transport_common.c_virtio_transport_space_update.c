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
struct vsock_sock {struct virtio_vsock_sock* trans; } ;
struct virtio_vsock_sock {int /*<<< orphan*/  tx_lock; void* peer_fwd_cnt; void* peer_buf_alloc; } ;
struct TYPE_2__ {int /*<<< orphan*/  fwd_cnt; int /*<<< orphan*/  buf_alloc; } ;
struct virtio_vsock_pkt {TYPE_1__ hdr; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int virtio_transport_has_space (struct vsock_sock*) ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 

__attribute__((used)) static bool virtio_transport_space_update(struct sock *sk,
					  struct virtio_vsock_pkt *pkt)
{
	struct vsock_sock *vsk = vsock_sk(sk);
	struct virtio_vsock_sock *vvs = vsk->trans;
	bool space_available;

	/* buf_alloc and fwd_cnt is always included in the hdr */
	spin_lock_bh(&vvs->tx_lock);
	vvs->peer_buf_alloc = le32_to_cpu(pkt->hdr.buf_alloc);
	vvs->peer_fwd_cnt = le32_to_cpu(pkt->hdr.fwd_cnt);
	space_available = virtio_transport_has_space(vsk);
	spin_unlock_bh(&vvs->tx_lock);
	return space_available;
}