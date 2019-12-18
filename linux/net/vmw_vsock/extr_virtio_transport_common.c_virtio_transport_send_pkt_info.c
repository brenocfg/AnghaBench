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
typedef  scalar_t__ u32 ;
struct TYPE_5__ {scalar_t__ svm_cid; scalar_t__ svm_port; } ;
struct TYPE_4__ {scalar_t__ svm_port; } ;
struct vsock_sock {struct virtio_vsock_sock* trans; TYPE_2__ remote_addr; TYPE_1__ local_addr; } ;
struct virtio_vsock_sock {int dummy; } ;
struct virtio_vsock_pkt_info {scalar_t__ pkt_len; scalar_t__ remote_cid; scalar_t__ remote_port; scalar_t__ op; } ;
struct virtio_vsock_pkt {int dummy; } ;
struct TYPE_6__ {int (* send_pkt ) (struct virtio_vsock_pkt*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ VIRTIO_VSOCK_MAX_PKT_BUF_SIZE ; 
 scalar_t__ VIRTIO_VSOCK_OP_RW ; 
 int stub1 (struct virtio_vsock_pkt*) ; 
 struct virtio_vsock_pkt* virtio_transport_alloc_pkt (struct virtio_vsock_pkt_info*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ virtio_transport_get_credit (struct virtio_vsock_sock*,scalar_t__) ; 
 TYPE_3__* virtio_transport_get_ops () ; 
 int /*<<< orphan*/  virtio_transport_inc_tx_pkt (struct virtio_vsock_sock*,struct virtio_vsock_pkt*) ; 
 int /*<<< orphan*/  virtio_transport_put_credit (struct virtio_vsock_sock*,scalar_t__) ; 
 scalar_t__ vm_sockets_get_local_cid () ; 

__attribute__((used)) static int virtio_transport_send_pkt_info(struct vsock_sock *vsk,
					  struct virtio_vsock_pkt_info *info)
{
	u32 src_cid, src_port, dst_cid, dst_port;
	struct virtio_vsock_sock *vvs;
	struct virtio_vsock_pkt *pkt;
	u32 pkt_len = info->pkt_len;

	src_cid = vm_sockets_get_local_cid();
	src_port = vsk->local_addr.svm_port;
	if (!info->remote_cid) {
		dst_cid	= vsk->remote_addr.svm_cid;
		dst_port = vsk->remote_addr.svm_port;
	} else {
		dst_cid = info->remote_cid;
		dst_port = info->remote_port;
	}

	vvs = vsk->trans;

	/* we can send less than pkt_len bytes */
	if (pkt_len > VIRTIO_VSOCK_MAX_PKT_BUF_SIZE)
		pkt_len = VIRTIO_VSOCK_MAX_PKT_BUF_SIZE;

	/* virtio_transport_get_credit might return less than pkt_len credit */
	pkt_len = virtio_transport_get_credit(vvs, pkt_len);

	/* Do not send zero length OP_RW pkt */
	if (pkt_len == 0 && info->op == VIRTIO_VSOCK_OP_RW)
		return pkt_len;

	pkt = virtio_transport_alloc_pkt(info, pkt_len,
					 src_cid, src_port,
					 dst_cid, dst_port);
	if (!pkt) {
		virtio_transport_put_credit(vvs, pkt_len);
		return -ENOMEM;
	}

	virtio_transport_inc_tx_pkt(vvs, pkt);

	return virtio_transport_get_ops()->send_pkt(pkt);
}