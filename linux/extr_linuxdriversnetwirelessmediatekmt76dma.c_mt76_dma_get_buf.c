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
typedef  int u32 ;
struct mt76_queue_entry {int /*<<< orphan*/ * buf; } ;
struct mt76_queue {int /*<<< orphan*/  buf_size; struct mt76_desc* desc; struct mt76_queue_entry* entry; } ;
struct mt76_dev {int /*<<< orphan*/  dev; } ;
struct mt76_desc {int /*<<< orphan*/  info; int /*<<< orphan*/  ctrl; int /*<<< orphan*/  buf0; } ;
typedef  void* dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int FIELD_GET (int /*<<< orphan*/ ,int) ; 
 int MT_DMA_CTL_LAST_SEC0 ; 
 int /*<<< orphan*/  MT_DMA_CTL_SD_LEN0 ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int SKB_WITH_OVERHEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
mt76_dma_get_buf(struct mt76_dev *dev, struct mt76_queue *q, int idx,
		 int *len, u32 *info, bool *more)
{
	struct mt76_queue_entry *e = &q->entry[idx];
	struct mt76_desc *desc = &q->desc[idx];
	dma_addr_t buf_addr;
	void *buf = e->buf;
	int buf_len = SKB_WITH_OVERHEAD(q->buf_size);

	buf_addr = le32_to_cpu(READ_ONCE(desc->buf0));
	if (len) {
		u32 ctl = le32_to_cpu(READ_ONCE(desc->ctrl));
		*len = FIELD_GET(MT_DMA_CTL_SD_LEN0, ctl);
		*more = !(ctl & MT_DMA_CTL_LAST_SEC0);
	}

	if (info)
		*info = le32_to_cpu(desc->info);

	dma_unmap_single(dev->dev, buf_addr, buf_len, DMA_FROM_DEVICE);
	e->buf = NULL;

	return buf;
}