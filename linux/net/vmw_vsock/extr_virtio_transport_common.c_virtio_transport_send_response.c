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
struct virtio_vsock_pkt_info {int reply; struct vsock_sock* vsk; int /*<<< orphan*/  remote_port; int /*<<< orphan*/  remote_cid; int /*<<< orphan*/  type; int /*<<< orphan*/  op; } ;
struct TYPE_2__ {int /*<<< orphan*/  src_port; int /*<<< orphan*/  src_cid; } ;
struct virtio_vsock_pkt {TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTIO_VSOCK_OP_RESPONSE ; 
 int /*<<< orphan*/  VIRTIO_VSOCK_TYPE_STREAM ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int virtio_transport_send_pkt_info (struct vsock_sock*,struct virtio_vsock_pkt_info*) ; 

__attribute__((used)) static int
virtio_transport_send_response(struct vsock_sock *vsk,
			       struct virtio_vsock_pkt *pkt)
{
	struct virtio_vsock_pkt_info info = {
		.op = VIRTIO_VSOCK_OP_RESPONSE,
		.type = VIRTIO_VSOCK_TYPE_STREAM,
		.remote_cid = le64_to_cpu(pkt->hdr.src_cid),
		.remote_port = le32_to_cpu(pkt->hdr.src_port),
		.reply = true,
		.vsk = vsk,
	};

	return virtio_transport_send_pkt_info(vsk, &info);
}