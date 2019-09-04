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
struct sk_buff {int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  inet6_is_jumbogram (struct sk_buff*) ; 
 int udp_skb_len (struct sk_buff*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int udp6_skb_len(struct sk_buff *skb)
{
	return unlikely(inet6_is_jumbogram(skb)) ? skb->len : udp_skb_len(skb);
}