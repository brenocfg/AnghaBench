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
struct virtio_input {int /*<<< orphan*/  lock; int /*<<< orphan*/  evt; int /*<<< orphan*/ * evts; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  virtinput_queue_evtbuf (struct virtio_input*,int /*<<< orphan*/ *) ; 
 int virtqueue_get_vring_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtqueue_kick (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void virtinput_fill_evt(struct virtio_input *vi)
{
	unsigned long flags;
	int i, size;

	spin_lock_irqsave(&vi->lock, flags);
	size = virtqueue_get_vring_size(vi->evt);
	if (size > ARRAY_SIZE(vi->evts))
		size = ARRAY_SIZE(vi->evts);
	for (i = 0; i < size; i++)
		virtinput_queue_evtbuf(vi, &vi->evts[i]);
	virtqueue_kick(vi->evt);
	spin_unlock_irqrestore(&vi->lock, flags);
}