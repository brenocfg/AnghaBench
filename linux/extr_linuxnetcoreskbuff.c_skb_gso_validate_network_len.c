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
 int /*<<< orphan*/  skb_gso_network_seglen (struct sk_buff const*) ; 
 int skb_gso_size_check (struct sk_buff const*,int /*<<< orphan*/ ,unsigned int) ; 

bool skb_gso_validate_network_len(const struct sk_buff *skb, unsigned int mtu)
{
	return skb_gso_size_check(skb, skb_gso_network_seglen(skb), mtu);
}