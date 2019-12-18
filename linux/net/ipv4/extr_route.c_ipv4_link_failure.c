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
struct rtable {int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  dst_set_expires (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv4_send_dest_unreach (struct sk_buff*) ; 
 struct rtable* skb_rtable (struct sk_buff*) ; 

__attribute__((used)) static void ipv4_link_failure(struct sk_buff *skb)
{
	struct rtable *rt;

	ipv4_send_dest_unreach(skb);

	rt = skb_rtable(skb);
	if (rt)
		dst_set_expires(&rt->dst, 0);
}