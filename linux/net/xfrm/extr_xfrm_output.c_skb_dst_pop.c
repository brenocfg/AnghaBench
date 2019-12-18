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
struct dst_entry {int dummy; } ;

/* Variables and functions */
 struct dst_entry* dst_clone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int /*<<< orphan*/  xfrm_dst_child (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dst_entry *skb_dst_pop(struct sk_buff *skb)
{
	struct dst_entry *child = dst_clone(xfrm_dst_child(skb_dst(skb)));

	skb_dst_drop(skb);
	return child;
}