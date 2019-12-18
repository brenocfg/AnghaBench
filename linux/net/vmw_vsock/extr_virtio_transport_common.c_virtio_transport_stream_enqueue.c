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
struct virtio_vsock_pkt_info {size_t pkt_len; struct vsock_sock* vsk; struct msghdr* msg; int /*<<< orphan*/  type; int /*<<< orphan*/  op; } ;
struct msghdr {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTIO_VSOCK_OP_RW ; 
 int /*<<< orphan*/  VIRTIO_VSOCK_TYPE_STREAM ; 
 int /*<<< orphan*/  virtio_transport_send_pkt_info (struct vsock_sock*,struct virtio_vsock_pkt_info*) ; 

ssize_t
virtio_transport_stream_enqueue(struct vsock_sock *vsk,
				struct msghdr *msg,
				size_t len)
{
	struct virtio_vsock_pkt_info info = {
		.op = VIRTIO_VSOCK_OP_RW,
		.type = VIRTIO_VSOCK_TYPE_STREAM,
		.msg = msg,
		.pkt_len = len,
		.vsk = vsk,
	};

	return virtio_transport_send_pkt_info(vsk, &info);
}