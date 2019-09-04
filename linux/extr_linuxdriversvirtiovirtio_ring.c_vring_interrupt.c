#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* callback ) (TYPE_1__*) ;} ;
struct vring_virtqueue {TYPE_1__ vq; int /*<<< orphan*/  broken; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  more_used (struct vring_virtqueue*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct vring_virtqueue*,...) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 struct vring_virtqueue* to_vvq (void*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

irqreturn_t vring_interrupt(int irq, void *_vq)
{
	struct vring_virtqueue *vq = to_vvq(_vq);

	if (!more_used(vq)) {
		pr_debug("virtqueue interrupt with no work for %p\n", vq);
		return IRQ_NONE;
	}

	if (unlikely(vq->broken))
		return IRQ_HANDLED;

	pr_debug("virtqueue callback for %p (%p)\n", vq, vq->vq.callback);
	if (vq->vq.callback)
		vq->vq.callback(&vq->vq);

	return IRQ_HANDLED;
}