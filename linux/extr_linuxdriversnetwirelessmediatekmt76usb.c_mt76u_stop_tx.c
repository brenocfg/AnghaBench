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
struct mt76_queue {int ndesc; TYPE_2__* entry; } ;
struct mt76_dev {struct mt76_queue* q_tx; } ;
struct TYPE_3__ {int /*<<< orphan*/  urb; } ;
struct TYPE_4__ {TYPE_1__ ubuf; } ;

/* Variables and functions */
 int IEEE80211_NUM_ACS ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mt76u_stop_tx(struct mt76_dev *dev)
{
	struct mt76_queue *q;
	int i, j;

	for (i = 0; i < IEEE80211_NUM_ACS; i++) {
		q = &dev->q_tx[i];
		for (j = 0; j < q->ndesc; j++)
			usb_kill_urb(q->entry[j].ubuf.urb);
	}
}