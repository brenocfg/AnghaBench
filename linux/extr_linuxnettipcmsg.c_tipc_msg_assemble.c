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
struct sk_buff_head {int dummy; } ;
struct sk_buff {int /*<<< orphan*/ * next; } ;

/* Variables and functions */
 struct sk_buff* __skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_purge (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int skb_queue_len (struct sk_buff_head*) ; 
 scalar_t__ tipc_buf_append (struct sk_buff**,struct sk_buff**) ; 

bool tipc_msg_assemble(struct sk_buff_head *list)
{
	struct sk_buff *skb, *tmp = NULL;

	if (skb_queue_len(list) == 1)
		return true;

	while ((skb = __skb_dequeue(list))) {
		skb->next = NULL;
		if (tipc_buf_append(&tmp, &skb)) {
			__skb_queue_tail(list, skb);
			return true;
		}
		if (!tmp)
			break;
	}
	__skb_queue_purge(list);
	__skb_queue_head_init(list);
	pr_warn("Failed do assemble buffer\n");
	return false;
}