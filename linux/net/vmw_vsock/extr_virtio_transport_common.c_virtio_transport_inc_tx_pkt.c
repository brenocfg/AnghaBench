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
struct virtio_vsock_sock {int /*<<< orphan*/  rx_lock; int /*<<< orphan*/  buf_alloc; int /*<<< orphan*/  fwd_cnt; int /*<<< orphan*/  last_fwd_cnt; } ;
struct TYPE_2__ {void* buf_alloc; void* fwd_cnt; } ;
struct virtio_vsock_pkt {TYPE_1__ hdr; } ;

/* Variables and functions */
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void virtio_transport_inc_tx_pkt(struct virtio_vsock_sock *vvs, struct virtio_vsock_pkt *pkt)
{
	spin_lock_bh(&vvs->rx_lock);
	vvs->last_fwd_cnt = vvs->fwd_cnt;
	pkt->hdr.fwd_cnt = cpu_to_le32(vvs->fwd_cnt);
	pkt->hdr.buf_alloc = cpu_to_le32(vvs->buf_alloc);
	spin_unlock_bh(&vvs->rx_lock);
}