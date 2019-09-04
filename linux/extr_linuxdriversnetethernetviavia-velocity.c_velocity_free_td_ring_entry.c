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
struct velocity_td_info {int nskb_dma; TYPE_2__* skb; scalar_t__* skb_dma; } ;
struct TYPE_3__ {struct velocity_td_info** infos; } ;
struct velocity_info {int /*<<< orphan*/  dev; TYPE_1__ tx; } ;
struct TYPE_4__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb (TYPE_2__*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void velocity_free_td_ring_entry(struct velocity_info *vptr,
							 int q, int n)
{
	struct velocity_td_info *td_info = &(vptr->tx.infos[q][n]);
	int i;

	if (td_info == NULL)
		return;

	if (td_info->skb) {
		for (i = 0; i < td_info->nskb_dma; i++) {
			if (td_info->skb_dma[i]) {
				dma_unmap_single(vptr->dev, td_info->skb_dma[i],
					td_info->skb->len, DMA_TO_DEVICE);
				td_info->skb_dma[i] = 0;
			}
		}
		dev_kfree_skb(td_info->skb);
		td_info->skb = NULL;
	}
}