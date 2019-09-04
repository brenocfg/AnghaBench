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
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data_len; scalar_t__ truesize; struct sk_buff* next; } ;
struct TYPE_4__ {struct sk_buff* last; } ;
struct TYPE_3__ {struct sk_buff* frag_list; } ;

/* Variables and functions */
 TYPE_2__* SCTP_OUTPUT_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_header_release (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

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

	__skb_header_release(skb);
}