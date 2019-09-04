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
struct skb_data {int state; } ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {scalar_t__ cb; } ;
typedef  enum skb_state { ____Placeholder_skb_state } skb_state ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 

__attribute__((used)) static void __usbnet_queue_skb(struct sk_buff_head *list,
			struct sk_buff *newsk, enum skb_state state)
{
	struct skb_data *entry = (struct skb_data *) newsk->cb;

	__skb_queue_tail(list, newsk);
	entry->state = state;
}