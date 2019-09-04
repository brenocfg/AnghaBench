#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct skb_shared_info {int nr_frags; TYPE_1__* frags; } ;
struct sk_buff {int end; int tail; int data_len; } ;
struct TYPE_7__ {int /*<<< orphan*/  frag0; } ;
struct TYPE_6__ {int page_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_5__* NAPI_GRO_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memmove (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  skb_frag_size (TYPE_1__*) ; 
 int /*<<< orphan*/  skb_frag_size_sub (TYPE_1__*,int) ; 
 int /*<<< orphan*/  skb_frag_unref (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct skb_shared_info* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_tail_pointer (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void gro_pull_from_frag0(struct sk_buff *skb, int grow)
{
	struct skb_shared_info *pinfo = skb_shinfo(skb);

	BUG_ON(skb->end - skb->tail < grow);

	memcpy(skb_tail_pointer(skb), NAPI_GRO_CB(skb)->frag0, grow);

	skb->data_len -= grow;
	skb->tail += grow;

	pinfo->frags[0].page_offset += grow;
	skb_frag_size_sub(&pinfo->frags[0], grow);

	if (unlikely(!skb_frag_size(&pinfo->frags[0]))) {
		skb_frag_unref(skb, 0);
		memmove(pinfo->frags, pinfo->frags + 1,
			--pinfo->nr_frags * sizeof(pinfo->frags[0]));
	}
}