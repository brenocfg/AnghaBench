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
struct sk_buff {int /*<<< orphan*/ * destructor; int /*<<< orphan*/  truesize; int /*<<< orphan*/  len; int /*<<< orphan*/  data_len; } ;
struct TYPE_2__ {struct sk_buff* frag_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  __copy_skb_header (struct sk_buff*,struct sk_buff*) ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

struct sk_buff *alloc_skb_for_msg(struct sk_buff *first)
{
	struct sk_buff *n;

	n = alloc_skb(0, GFP_ATOMIC);
	if (!n)
		return NULL;

	n->len = first->len;
	n->data_len = first->len;
	n->truesize = first->truesize;

	skb_shinfo(n)->frag_list = first;

	__copy_skb_header(n, first);
	n->destructor = NULL;

	return n;
}