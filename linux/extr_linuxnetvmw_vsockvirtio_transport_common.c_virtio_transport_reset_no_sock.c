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
struct virtio_vsock_pkt_info {scalar_t__ op; scalar_t__ type; int reply; } ;
struct TYPE_3__ {int /*<<< orphan*/  src_port; int /*<<< orphan*/  src_cid; int /*<<< orphan*/  dst_port; int /*<<< orphan*/  dst_cid; int /*<<< orphan*/  op; int /*<<< orphan*/  type; } ;
struct virtio_vsock_pkt {TYPE_1__ hdr; } ;
struct TYPE_4__ {int (* send_pkt ) (struct virtio_vsock_pkt*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ VIRTIO_VSOCK_OP_RST ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int stub1 (struct virtio_vsock_pkt*) ; 
 struct virtio_vsock_pkt* virtio_transport_alloc_pkt (struct virtio_vsock_pkt_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* virtio_transport_get_ops () ; 

__attribute__((used)) static int virtio_transport_reset_no_sock(struct virtio_vsock_pkt *pkt)
{
	struct virtio_vsock_pkt_info info = {
		.op = VIRTIO_VSOCK_OP_RST,
		.type = le16_to_cpu(pkt->hdr.type),
		.reply = true,
	};

	/* Send RST only if the original pkt is not a RST pkt */
	if (le16_to_cpu(pkt->hdr.op) == VIRTIO_VSOCK_OP_RST)
		return 0;

	pkt = virtio_transport_alloc_pkt(&info, 0,
					 le64_to_cpu(pkt->hdr.dst_cid),
					 le32_to_cpu(pkt->hdr.dst_port),
					 le64_to_cpu(pkt->hdr.src_cid),
					 le32_to_cpu(pkt->hdr.src_port));
	if (!pkt)
		return -ENOMEM;

	return virtio_transport_get_ops()->send_pkt(pkt);
}