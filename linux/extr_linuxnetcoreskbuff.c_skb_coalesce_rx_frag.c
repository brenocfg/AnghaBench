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
struct sk_buff {int len; int data_len; unsigned int truesize; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_2__ {int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  skb_frag_size_add (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

void skb_coalesce_rx_frag(struct sk_buff *skb, int i, int size,
			  unsigned int truesize)
{
	skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

	skb_frag_size_add(frag, size);
	skb->len += size;
	skb->data_len += size;
	skb->truesize += truesize;
}