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
typedef  int /*<<< orphan*/  u64 ;
struct vsock_sock {struct virtio_vsock_sock* trans; } ;
struct virtio_vsock_sock {int /*<<< orphan*/  buf_size_max; } ;

/* Variables and functions */

u64 virtio_transport_get_max_buffer_size(struct vsock_sock *vsk)
{
	struct virtio_vsock_sock *vvs = vsk->trans;

	return vvs->buf_size_max;
}