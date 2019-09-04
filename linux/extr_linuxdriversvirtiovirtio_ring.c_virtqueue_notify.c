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
struct vring_virtqueue {int broken; int /*<<< orphan*/  (* notify ) (struct virtqueue*) ;} ;
struct virtqueue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct virtqueue*) ; 
 struct vring_virtqueue* to_vvq (struct virtqueue*) ; 
 scalar_t__ unlikely (int) ; 

bool virtqueue_notify(struct virtqueue *_vq)
{
	struct vring_virtqueue *vq = to_vvq(_vq);

	if (unlikely(vq->broken))
		return false;

	/* Prod other side to tell it about changes. */
	if (!vq->notify(_vq)) {
		vq->broken = true;
		return false;
	}
	return true;
}