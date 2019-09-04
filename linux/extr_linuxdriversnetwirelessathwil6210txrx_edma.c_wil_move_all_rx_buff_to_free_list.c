#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  size_t u16 ;
struct TYPE_12__ {int /*<<< orphan*/  length; } ;
struct TYPE_9__ {int /*<<< orphan*/  buff_id; } ;
struct wil_rx_enhanced_desc {TYPE_6__ dma; TYPE_3__ mac; } ;
struct wil_ring {int swhead; int size; int swtail; TYPE_2__* va; } ;
struct TYPE_11__ {size_t size; int /*<<< orphan*/  free; TYPE_4__* buff_arr; } ;
struct wil6210_priv {TYPE_5__ rx_buff_mgmt; } ;
struct sk_buff {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_10__ {int /*<<< orphan*/  list; struct sk_buff* skb; } ;
struct TYPE_7__ {int /*<<< orphan*/  enhanced; } ;
struct TYPE_8__ {TYPE_1__ rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 size_t __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*,size_t) ; 
 int wil_ring_next_tail (struct wil_ring*) ; 
 int /*<<< orphan*/  wil_rx_desc_get_addr_edma (TYPE_6__*) ; 
 struct device* wil_to_dev (struct wil6210_priv*) ; 

__attribute__((used)) static void wil_move_all_rx_buff_to_free_list(struct wil6210_priv *wil,
					      struct wil_ring *ring)
{
	struct device *dev = wil_to_dev(wil);
	u32 next_tail;
	u32 swhead = (ring->swhead + 1) % ring->size;
	dma_addr_t pa;
	u16 dmalen;

	for (; next_tail = wil_ring_next_tail(ring), (next_tail != swhead);
	     ring->swtail = next_tail) {
		struct wil_rx_enhanced_desc dd, *d = &dd;
		struct wil_rx_enhanced_desc *_d =
			(struct wil_rx_enhanced_desc *)
			&ring->va[ring->swtail].rx.enhanced;
		struct sk_buff *skb;
		u16 buff_id;

		*d = *_d;

		/* Extract the SKB from the rx_buff management array */
		buff_id = __le16_to_cpu(d->mac.buff_id);
		if (buff_id >= wil->rx_buff_mgmt.size) {
			wil_err(wil, "invalid buff_id %d\n", buff_id);
			continue;
		}
		skb = wil->rx_buff_mgmt.buff_arr[buff_id].skb;
		wil->rx_buff_mgmt.buff_arr[buff_id].skb = NULL;
		if (unlikely(!skb)) {
			wil_err(wil, "No Rx skb at buff_id %d\n", buff_id);
		} else {
			pa = wil_rx_desc_get_addr_edma(&d->dma);
			dmalen = le16_to_cpu(d->dma.length);
			dma_unmap_single(dev, pa, dmalen, DMA_FROM_DEVICE);

			kfree_skb(skb);
		}

		/* Move the buffer from the active to the free list */
		list_move(&wil->rx_buff_mgmt.buff_arr[buff_id].list,
			  &wil->rx_buff_mgmt.free);
	}
}