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
typedef  size_t u32 ;
struct device {int dummy; } ;
struct TYPE_3__ {scalar_t__ counter; } ;
struct brcmf_msgbuf_pktids {size_t array_size; TYPE_2__* skb; int /*<<< orphan*/  direction; scalar_t__ data_offset; int /*<<< orphan*/  physaddr; TYPE_1__ allocated; struct brcmf_msgbuf_pktids* array; } ;
struct brcmf_msgbuf_pktid {size_t array_size; TYPE_2__* skb; int /*<<< orphan*/  direction; scalar_t__ data_offset; int /*<<< orphan*/  physaddr; TYPE_1__ allocated; struct brcmf_msgbuf_pktid* array; } ;
struct TYPE_4__ {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcmu_pkt_buf_free_skb (TYPE_2__*) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct brcmf_msgbuf_pktids*) ; 

__attribute__((used)) static void
brcmf_msgbuf_release_array(struct device *dev,
			   struct brcmf_msgbuf_pktids *pktids)
{
	struct brcmf_msgbuf_pktid *array;
	struct brcmf_msgbuf_pktid *pktid;
	u32 count;

	array = pktids->array;
	count = 0;
	do {
		if (array[count].allocated.counter) {
			pktid = &array[count];
			dma_unmap_single(dev, pktid->physaddr,
					 pktid->skb->len - pktid->data_offset,
					 pktids->direction);
			brcmu_pkt_buf_free_skb(pktid->skb);
		}
		count++;
	} while (count < pktids->array_size);

	kfree(array);
	kfree(pktids);
}