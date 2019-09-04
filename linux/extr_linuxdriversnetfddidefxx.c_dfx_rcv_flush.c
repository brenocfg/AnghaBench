#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/ ** p_rcv_buff_va; TYPE_2__* descr_block_virt; int /*<<< orphan*/  bus_dev; scalar_t__ rcv_bufs_to_post; } ;
struct TYPE_6__ {TYPE_1__* rcv_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  long_1; } ;
typedef  TYPE_3__ DFX_board_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 scalar_t__ PI_RCV_DATA_K_NUM_ENTRIES ; 
 int /*<<< orphan*/  PI_RCV_DATA_K_SIZE_MAX ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dfx_rcv_flush( DFX_board_t *bp )
	{
	int i, j;

	for (i = 0; i < (int)(bp->rcv_bufs_to_post); i++)
		for (j = 0; (i + j) < (int)PI_RCV_DATA_K_NUM_ENTRIES; j += bp->rcv_bufs_to_post)
		{
			struct sk_buff *skb;
			skb = (struct sk_buff *)bp->p_rcv_buff_va[i+j];
			if (skb) {
				dma_unmap_single(bp->bus_dev,
						 bp->descr_block_virt->rcv_data[i+j].long_1,
						 PI_RCV_DATA_K_SIZE_MAX,
						 DMA_FROM_DEVICE);
				dev_kfree_skb(skb);
			}
			bp->p_rcv_buff_va[i+j] = NULL;
		}

	}