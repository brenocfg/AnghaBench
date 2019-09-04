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
struct vhost_virtqueue {int is_le; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTIO_F_VERSION_1 ; 
 scalar_t__ vhost_has_feature (struct vhost_virtqueue*,int /*<<< orphan*/ ) ; 
 scalar_t__ virtio_legacy_is_little_endian () ; 

__attribute__((used)) static void vhost_init_is_le(struct vhost_virtqueue *vq)
{
	vq->is_le = vhost_has_feature(vq, VIRTIO_F_VERSION_1)
		|| virtio_legacy_is_little_endian();
}