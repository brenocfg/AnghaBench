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
struct sk_buff {struct sk_buff* next; } ;

/* Variables and functions */
 struct sk_buff* defer_kfree_skb_list ; 

void rtnl_kfree_skbs(struct sk_buff *head, struct sk_buff *tail)
{
	if (head && tail) {
		tail->next = defer_kfree_skb_list;
		defer_kfree_skb_list = head;
	}
}