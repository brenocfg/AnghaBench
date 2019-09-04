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
typedef  int u8 ;
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct pn533 {int /*<<< orphan*/  fragment_skb; int /*<<< orphan*/  tgt_mode; } ;

/* Variables and functions */
 int PN533_CMD_DATAFRAME_MAXLEN ; 
 int PN533_CMD_MI_MASK ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct sk_buff* pn533_alloc_skb (struct pn533*,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static int pn533_fill_fragment_skbs(struct pn533 *dev, struct sk_buff *skb)
{
	struct sk_buff *frag;
	int  frag_size;

	do {
		/* Remaining size */
		if (skb->len > PN533_CMD_DATAFRAME_MAXLEN)
			frag_size = PN533_CMD_DATAFRAME_MAXLEN;
		else
			frag_size = skb->len;

		/* Allocate and reserve */
		frag = pn533_alloc_skb(dev, frag_size);
		if (!frag) {
			skb_queue_purge(&dev->fragment_skb);
			break;
		}

		if (!dev->tgt_mode) {
			/* Reserve the TG/MI byte */
			skb_reserve(frag, 1);

			/* MI + TG */
			if (frag_size  == PN533_CMD_DATAFRAME_MAXLEN)
				*(u8 *)skb_push(frag, sizeof(u8)) =
						(PN533_CMD_MI_MASK | 1);
			else
				*(u8 *)skb_push(frag, sizeof(u8)) =  1; /* TG */
		}

		skb_put_data(frag, skb->data, frag_size);

		/* Reduce the size of incoming buffer */
		skb_pull(skb, frag_size);

		/* Add this to skb_queue */
		skb_queue_tail(&dev->fragment_skb, frag);

	} while (skb->len > 0);

	dev_kfree_skb(skb);

	return skb_queue_len(&dev->fragment_skb);
}