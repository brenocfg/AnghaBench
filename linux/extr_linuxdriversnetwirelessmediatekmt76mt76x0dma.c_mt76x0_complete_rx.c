#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct urb {int /*<<< orphan*/  status; struct mt76x0_dev* context; } ;
struct mt76x0_rx_queue {size_t end; int entries; int /*<<< orphan*/  pending; TYPE_2__* e; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct mt76x0_dev {int /*<<< orphan*/  rx_lock; int /*<<< orphan*/  rx_tasklet; TYPE_1__ mt76; struct mt76x0_rx_queue rx_q; } ;
struct TYPE_4__ {struct urb* urb; } ;

/* Variables and functions */
 scalar_t__ WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ mt76x0_urb_has_error (struct urb*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mt76x0_complete_rx(struct urb *urb)
{
	struct mt76x0_dev *dev = urb->context;
	struct mt76x0_rx_queue *q = &dev->rx_q;
	unsigned long flags;

	spin_lock_irqsave(&dev->rx_lock, flags);

	if (mt76x0_urb_has_error(urb))
		dev_err(dev->mt76.dev, "Error: RX urb failed:%d\n", urb->status);
	if (WARN_ONCE(q->e[q->end].urb != urb, "RX urb mismatch"))
		goto out;

	q->end = (q->end + 1) % q->entries;
	q->pending++;
	tasklet_schedule(&dev->rx_tasklet);
out:
	spin_unlock_irqrestore(&dev->rx_lock, flags);
}