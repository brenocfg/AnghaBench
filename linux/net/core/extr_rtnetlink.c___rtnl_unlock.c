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
 int /*<<< orphan*/  cond_resched () ; 
 struct sk_buff* defer_kfree_skb_list ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtnl_mutex ; 

void __rtnl_unlock(void)
{
	struct sk_buff *head = defer_kfree_skb_list;

	defer_kfree_skb_list = NULL;

	mutex_unlock(&rtnl_mutex);

	while (head) {
		struct sk_buff *next = head->next;

		kfree_skb(head);
		cond_resched();
		head = next;
	}
}