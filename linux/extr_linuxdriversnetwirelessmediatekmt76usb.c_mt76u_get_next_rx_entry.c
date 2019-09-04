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
struct mt76u_buf {int dummy; } ;
struct mt76_queue {scalar_t__ queued; size_t head; int ndesc; int /*<<< orphan*/  lock; TYPE_1__* entry; } ;
struct TYPE_2__ {struct mt76u_buf ubuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline struct mt76u_buf
*mt76u_get_next_rx_entry(struct mt76_queue *q)
{
	struct mt76u_buf *buf = NULL;
	unsigned long flags;

	spin_lock_irqsave(&q->lock, flags);
	if (q->queued > 0) {
		buf = &q->entry[q->head].ubuf;
		q->head = (q->head + 1) % q->ndesc;
		q->queued--;
	}
	spin_unlock_irqrestore(&q->lock, flags);

	return buf;
}