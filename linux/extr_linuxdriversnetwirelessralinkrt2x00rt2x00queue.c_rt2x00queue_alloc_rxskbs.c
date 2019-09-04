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
struct sk_buff {int dummy; } ;
struct data_queue {unsigned int limit; TYPE_1__* entries; } ;
struct TYPE_2__ {struct sk_buff* skb; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct sk_buff* rt2x00queue_alloc_rxskb (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt2x00queue_alloc_rxskbs(struct data_queue *queue)
{
	unsigned int i;
	struct sk_buff *skb;

	for (i = 0; i < queue->limit; i++) {
		skb = rt2x00queue_alloc_rxskb(&queue->entries[i], GFP_KERNEL);
		if (!skb)
			return -ENOMEM;
		queue->entries[i].skb = skb;
	}

	return 0;
}