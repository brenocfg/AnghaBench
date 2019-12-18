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
struct sk_buff {int encapsulation; } ;
struct TYPE_2__ {int /*<<< orphan*/  gso_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  SKB_GSO_IPXIP4 ; 
 int ipv6_gro_complete (struct sk_buff*,int) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static int sit_gro_complete(struct sk_buff *skb, int nhoff)
{
	skb->encapsulation = 1;
	skb_shinfo(skb)->gso_type |= SKB_GSO_IPXIP4;
	return ipv6_gro_complete(skb, nhoff);
}