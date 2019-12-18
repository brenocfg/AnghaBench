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
struct sk_buff {int /*<<< orphan*/  tc_index; int /*<<< orphan*/  mark; int /*<<< orphan*/  dev; int /*<<< orphan*/  protocol; int /*<<< orphan*/  priority; int /*<<< orphan*/  pkt_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  dst_clone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_copy (struct sk_buff*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_copy_hash (struct sk_buff*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_copy_secmark (struct sk_buff*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_ext_copy (struct sk_buff*,struct sk_buff*) ; 

__attribute__((used)) static void ip6_copy_metadata(struct sk_buff *to, struct sk_buff *from)
{
	to->pkt_type = from->pkt_type;
	to->priority = from->priority;
	to->protocol = from->protocol;
	skb_dst_drop(to);
	skb_dst_set(to, dst_clone(skb_dst(from)));
	to->dev = from->dev;
	to->mark = from->mark;

	skb_copy_hash(to, from);

#ifdef CONFIG_NET_SCHED
	to->tc_index = from->tc_index;
#endif
	nf_copy(to, from);
	skb_ext_copy(to, from);
	skb_copy_secmark(to, from);
}