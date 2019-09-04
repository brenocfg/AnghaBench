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
typedef  int /*<<< orphan*/  u32 ;
struct mt76_queue {int tail; int ndesc; int /*<<< orphan*/  queued; TYPE_1__* desc; } ;
struct mt76_dev {int dummy; } ;
struct TYPE_2__ {int ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_DMA_CTL_DMA_DONE ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* mt76_dma_get_buf (struct mt76_dev*,struct mt76_queue*,int,int*,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static void *
mt76_dma_dequeue(struct mt76_dev *dev, struct mt76_queue *q, bool flush,
		 int *len, u32 *info, bool *more)
{
	int idx = q->tail;

	*more = false;
	if (!q->queued)
		return NULL;

	if (!flush && !(q->desc[idx].ctrl & cpu_to_le32(MT_DMA_CTL_DMA_DONE)))
		return NULL;

	q->tail = (q->tail + 1) % q->ndesc;
	q->queued--;

	return mt76_dma_get_buf(dev, q, idx, len, info, more);
}