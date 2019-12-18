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
struct list_head {int dummy; } ;
struct TYPE_2__ {int encap_mark; int flush; } ;

/* Variables and functions */
 TYPE_1__* NAPI_GRO_CB (struct sk_buff*) ; 
 struct sk_buff* ipv6_gro_receive (struct list_head*,struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *sit_ip6ip6_gro_receive(struct list_head *head,
					      struct sk_buff *skb)
{
	/* Common GRO receive for SIT and IP6IP6 */

	if (NAPI_GRO_CB(skb)->encap_mark) {
		NAPI_GRO_CB(skb)->flush = 1;
		return NULL;
	}

	NAPI_GRO_CB(skb)->encap_mark = 1;

	return ipv6_gro_receive(head, skb);
}