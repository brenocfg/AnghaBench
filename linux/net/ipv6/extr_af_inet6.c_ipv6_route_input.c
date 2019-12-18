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
struct TYPE_2__ {int error; } ;

/* Variables and functions */
 int /*<<< orphan*/  ip6_route_input (struct sk_buff*) ; 
 TYPE_1__* skb_dst (struct sk_buff*) ; 

__attribute__((used)) static int ipv6_route_input(struct sk_buff *skb)
{
	ip6_route_input(skb);
	return skb_dst(skb)->error;
}