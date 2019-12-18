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
struct virtio_vsock_pkt_info {int flags; struct vsock_sock* vsk; int /*<<< orphan*/  type; int /*<<< orphan*/  op; } ;

/* Variables and functions */
 int RCV_SHUTDOWN ; 
 int SEND_SHUTDOWN ; 
 int /*<<< orphan*/  VIRTIO_VSOCK_OP_SHUTDOWN ; 
 int VIRTIO_VSOCK_SHUTDOWN_RCV ; 
 int VIRTIO_VSOCK_SHUTDOWN_SEND ; 
 int /*<<< orphan*/  VIRTIO_VSOCK_TYPE_STREAM ; 
 int virtio_transport_send_pkt_info (struct vsock_sock*,struct virtio_vsock_pkt_info*) ; 

int virtio_transport_shutdown(struct vsock_sock *vsk, int mode)
{
	struct virtio_vsock_pkt_info info = {
		.op = VIRTIO_VSOCK_OP_SHUTDOWN,
		.type = VIRTIO_VSOCK_TYPE_STREAM,
		.flags = (mode & RCV_SHUTDOWN ?
			  VIRTIO_VSOCK_SHUTDOWN_RCV : 0) |
			 (mode & SEND_SHUTDOWN ?
			  VIRTIO_VSOCK_SHUTDOWN_SEND : 0),
		.vsk = vsk,
	};

	return virtio_transport_send_pkt_info(vsk, &info);
}