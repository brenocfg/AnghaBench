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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct page {int dummy; } ;
struct mt76x0_dma_buf_rx {struct page* p; TYPE_1__* urb; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
struct mt76x0_dev {TYPE_2__ mt76; } ;
struct TYPE_3__ {int actual_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT76_STATE_INITIALIZED ; 
 int /*<<< orphan*/  MT_RX_ORDER ; 
 int /*<<< orphan*/  __free_pages (struct page*,int /*<<< orphan*/ ) ; 
 struct page* dev_alloc_pages (int /*<<< orphan*/ ) ; 
 int mt76x0_rx_next_seg_len (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mt76x0_rx_process_seg (struct mt76x0_dev*,int /*<<< orphan*/ *,int,struct page*) ; 
 int /*<<< orphan*/ * page_address (struct page*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_mt76x0_rx_dma_aggr (TYPE_2__*,int,int) ; 

__attribute__((used)) static void
mt76x0_rx_process_entry(struct mt76x0_dev *dev, struct mt76x0_dma_buf_rx *e)
{
	u32 seg_len, data_len = e->urb->actual_length;
	u8 *data = page_address(e->p);
	struct page *new_p = NULL;
	int cnt = 0;

	if (!test_bit(MT76_STATE_INITIALIZED, &dev->mt76.state))
		return;

	/* Copy if there is very little data in the buffer. */
	if (data_len > 512)
		new_p = dev_alloc_pages(MT_RX_ORDER);

	while ((seg_len = mt76x0_rx_next_seg_len(data, data_len))) {
		mt76x0_rx_process_seg(dev, data, seg_len, new_p ? e->p : NULL);

		data_len -= seg_len;
		data += seg_len;
		cnt++;
	}

	if (cnt > 1)
		trace_mt76x0_rx_dma_aggr(&dev->mt76, cnt, !!new_p);

	if (new_p) {
		/* we have one extra ref from the allocator */
		__free_pages(e->p, MT_RX_ORDER);

		e->p = new_p;
	}
}