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
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_skbmem (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_release_data (struct sk_buff*) ; 
 int /*<<< orphan*/  trace_consume_skb (struct sk_buff*) ; 

void __consume_stateless_skb(struct sk_buff *skb)
{
	trace_consume_skb(skb);
	skb_release_data(skb);
	kfree_skbmem(skb);
}