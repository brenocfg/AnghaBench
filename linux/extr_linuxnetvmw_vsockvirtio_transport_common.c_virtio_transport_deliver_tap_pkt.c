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
struct virtio_vsock_pkt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  virtio_transport_build_skb ; 
 int /*<<< orphan*/  vsock_deliver_tap (int /*<<< orphan*/ ,struct virtio_vsock_pkt*) ; 

void virtio_transport_deliver_tap_pkt(struct virtio_vsock_pkt *pkt)
{
	vsock_deliver_tap(virtio_transport_build_skb, pkt);
}