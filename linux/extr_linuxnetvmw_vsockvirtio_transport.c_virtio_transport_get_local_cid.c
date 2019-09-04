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
typedef  int /*<<< orphan*/  u32 ;
struct virtio_vsock {int /*<<< orphan*/  guest_cid; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMADDR_CID_ANY ; 
 struct virtio_vsock* virtio_vsock_get () ; 

__attribute__((used)) static u32 virtio_transport_get_local_cid(void)
{
	struct virtio_vsock *vsock = virtio_vsock_get();

	if (!vsock)
		return VMADDR_CID_ANY;

	return vsock->guest_cid;
}