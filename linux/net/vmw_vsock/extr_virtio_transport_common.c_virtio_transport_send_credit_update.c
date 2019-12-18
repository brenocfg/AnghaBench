#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vsock_sock {int dummy; } ;
struct virtio_vsock_pkt_info {int type; struct vsock_sock* vsk; int /*<<< orphan*/  op; } ;
struct virtio_vsock_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTIO_VSOCK_OP_CREDIT_UPDATE ; 
 int virtio_transport_send_pkt_info (struct vsock_sock*,struct virtio_vsock_pkt_info*) ; 

__attribute__((used)) static int virtio_transport_send_credit_update(struct vsock_sock *vsk,
					       int type,
					       struct virtio_vsock_hdr *hdr)
{
	struct virtio_vsock_pkt_info info = {
		.op = VIRTIO_VSOCK_OP_CREDIT_UPDATE,
		.type = type,
		.vsk = vsk,
	};

	return virtio_transport_send_pkt_info(vsk, &info);
}