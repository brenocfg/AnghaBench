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
struct vring_used_elem {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct vhost_virtqueue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_vhost32 (struct vhost_virtqueue*,int) ; 
 int vhost_add_used_n (struct vhost_virtqueue*,struct vring_used_elem*,int) ; 

int vhost_add_used(struct vhost_virtqueue *vq, unsigned int head, int len)
{
	struct vring_used_elem heads = {
		cpu_to_vhost32(vq, head),
		cpu_to_vhost32(vq, len)
	};

	return vhost_add_used_n(vq, &heads, 1);
}