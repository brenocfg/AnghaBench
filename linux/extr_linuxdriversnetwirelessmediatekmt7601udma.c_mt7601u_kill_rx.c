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
struct TYPE_4__ {int entries; int end; TYPE_1__* e; } ;
struct mt7601u_dev {int /*<<< orphan*/  rx_lock; TYPE_2__ rx_q; } ;
struct TYPE_3__ {int /*<<< orphan*/  urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_poison_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mt7601u_kill_rx(struct mt7601u_dev *dev)
{
	int i;
	unsigned long flags;

	spin_lock_irqsave(&dev->rx_lock, flags);

	for (i = 0; i < dev->rx_q.entries; i++) {
		int next = dev->rx_q.end;

		spin_unlock_irqrestore(&dev->rx_lock, flags);
		usb_poison_urb(dev->rx_q.e[next].urb);
		spin_lock_irqsave(&dev->rx_lock, flags);
	}

	spin_unlock_irqrestore(&dev->rx_lock, flags);
}