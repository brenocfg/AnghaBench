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
struct TYPE_2__ {int flush; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 TYPE_1__* NAPI_GRO_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  ip6_gro_compute_pseudo ; 
 scalar_t__ skb_gro_checksum_validate (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* tcp_gro_receive (struct list_head*,struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *tcp6_gro_receive(struct list_head *head,
					struct sk_buff *skb)
{
	/* Don't bother verifying checksum if we're going to flush anyway. */
	if (!NAPI_GRO_CB(skb)->flush &&
	    skb_gro_checksum_validate(skb, IPPROTO_TCP,
				      ip6_gro_compute_pseudo)) {
		NAPI_GRO_CB(skb)->flush = 1;
		return NULL;
	}

	return tcp_gro_receive(head, skb);
}