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
struct urb {int /*<<< orphan*/  status; struct mt7601u_dev* context; } ;
struct mt7601u_rx_queue {size_t end; int entries; int /*<<< orphan*/  pending; TYPE_1__* e; } ;
struct mt7601u_dev {int /*<<< orphan*/  rx_lock; int /*<<< orphan*/  rx_tasklet; int /*<<< orphan*/  dev; struct mt7601u_rx_queue rx_q; } ;
struct TYPE_2__ {struct urb* urb; } ;

/* Variables and functions */
 scalar_t__ WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ mt7601u_urb_has_error (struct urb*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mt7601u_complete_rx(struct urb *urb)
{
	struct mt7601u_dev *dev = urb->context;
	struct mt7601u_rx_queue *q = &dev->rx_q;
	unsigned long flags;

	spin_lock_irqsave(&dev->rx_lock, flags);

	if (mt7601u_urb_has_error(urb))
		dev_err(dev->dev, "Error: RX urb failed:%d\n", urb->status);
	if (WARN_ONCE(q->e[q->end].urb != urb, "RX urb mismatch"))
		goto out;

	q->end = (q->end + 1) % q->entries;
	q->pending++;
	tasklet_schedule(&dev->rx_tasklet);
out:
	spin_unlock_irqrestore(&dev->rx_lock, flags);
}