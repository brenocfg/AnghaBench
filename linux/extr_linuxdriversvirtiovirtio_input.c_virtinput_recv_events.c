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
struct virtqueue {TYPE_1__* vdev; } ;
struct virtio_input_event {int /*<<< orphan*/  value; int /*<<< orphan*/  code; int /*<<< orphan*/  type; } ;
struct virtio_input {int /*<<< orphan*/  lock; int /*<<< orphan*/  idev; int /*<<< orphan*/  evt; scalar_t__ ready; } ;
struct TYPE_2__ {struct virtio_input* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  virtinput_queue_evtbuf (struct virtio_input*,struct virtio_input_event*) ; 
 struct virtio_input_event* virtqueue_get_buf (int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  virtqueue_kick (struct virtqueue*) ; 

__attribute__((used)) static void virtinput_recv_events(struct virtqueue *vq)
{
	struct virtio_input *vi = vq->vdev->priv;
	struct virtio_input_event *event;
	unsigned long flags;
	unsigned int len;

	spin_lock_irqsave(&vi->lock, flags);
	if (vi->ready) {
		while ((event = virtqueue_get_buf(vi->evt, &len)) != NULL) {
			spin_unlock_irqrestore(&vi->lock, flags);
			input_event(vi->idev,
				    le16_to_cpu(event->type),
				    le16_to_cpu(event->code),
				    le32_to_cpu(event->value));
			spin_lock_irqsave(&vi->lock, flags);
			virtinput_queue_evtbuf(vi, event);
		}
		virtqueue_kick(vq);
	}
	spin_unlock_irqrestore(&vi->lock, flags);
}