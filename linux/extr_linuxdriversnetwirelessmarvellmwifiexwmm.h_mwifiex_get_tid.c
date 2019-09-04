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
struct sk_buff {int priority; } ;
struct mwifiex_ra_list_tbl {int /*<<< orphan*/  skb_head; } ;

/* Variables and functions */
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
mwifiex_get_tid(struct mwifiex_ra_list_tbl *ptr)
{
	struct sk_buff *skb;

	if (skb_queue_empty(&ptr->skb_head))
		return 0;

	skb = skb_peek(&ptr->skb_head);

	return skb->priority;
}