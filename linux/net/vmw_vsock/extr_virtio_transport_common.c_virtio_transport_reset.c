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
struct vsock_sock {int dummy; } ;
struct virtio_vsock_pkt_info {scalar_t__ op; int reply; struct vsock_sock* vsk; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  op; } ;
struct virtio_vsock_pkt {TYPE_1__ hdr; } ;

/* Variables and functions */
 scalar_t__ VIRTIO_VSOCK_OP_RST ; 
 int /*<<< orphan*/  VIRTIO_VSOCK_TYPE_STREAM ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int virtio_transport_send_pkt_info (struct vsock_sock*,struct virtio_vsock_pkt_info*) ; 

__attribute__((used)) static int virtio_transport_reset(struct vsock_sock *vsk,
				  struct virtio_vsock_pkt *pkt)
{
	struct virtio_vsock_pkt_info info = {
		.op = VIRTIO_VSOCK_OP_RST,
		.type = VIRTIO_VSOCK_TYPE_STREAM,
		.reply = !!pkt,
		.vsk = vsk,
	};

	/* Send RST only if the original pkt is not a RST pkt */
	if (pkt && le16_to_cpu(pkt->hdr.op) == VIRTIO_VSOCK_OP_RST)
		return 0;

	return virtio_transport_send_pkt_info(vsk, &info);
}