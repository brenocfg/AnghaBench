#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {TYPE_1__* sk; scalar_t__ truesize; scalar_t__ len; int /*<<< orphan*/  data_len; struct sk_buff* next; } ;
struct TYPE_6__ {struct sk_buff* last; } ;
struct TYPE_5__ {struct sk_buff* frag_list; } ;
struct TYPE_4__ {int /*<<< orphan*/  sk_wmem_alloc; } ;

/* Variables and functions */
 TYPE_3__* SCTP_OUTPUT_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_header_release (struct sk_buff*) ; 
 int /*<<< orphan*/  refcount_add (scalar_t__,int /*<<< orphan*/ *) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void sctp_packet_gso_append(struct sk_buff *head, struct sk_buff *skb)
{
	if (SCTP_OUTPUT_CB(head)->last == head)
		skb_shinfo(head)->frag_list = skb;
	else
		SCTP_OUTPUT_CB(head)->last->next = skb;
	SCTP_OUTPUT_CB(head)->last = skb;

	head->truesize += skb->truesize;
	head->data_len += skb->len;
	head->len += skb->len;
	refcount_add(skb->truesize, &head->sk->sk_wmem_alloc);

	__skb_header_release(skb);
}