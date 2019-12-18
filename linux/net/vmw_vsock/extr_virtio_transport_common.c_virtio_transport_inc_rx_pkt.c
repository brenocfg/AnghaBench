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
struct virtio_vsock_sock {scalar_t__ rx_bytes; scalar_t__ buf_alloc; } ;
struct virtio_vsock_pkt {scalar_t__ len; } ;

/* Variables and functions */

__attribute__((used)) static bool virtio_transport_inc_rx_pkt(struct virtio_vsock_sock *vvs,
					struct virtio_vsock_pkt *pkt)
{
	if (vvs->rx_bytes + pkt->len > vvs->buf_alloc)
		return false;

	vvs->rx_bytes += pkt->len;
	return true;
}