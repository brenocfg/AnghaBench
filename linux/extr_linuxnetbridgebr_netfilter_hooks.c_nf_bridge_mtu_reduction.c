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
struct sk_buff {TYPE_1__* nf_bridge; } ;
struct TYPE_2__ {scalar_t__ orig_proto; } ;

/* Variables and functions */
 scalar_t__ BRNF_PROTO_PPPOE ; 
 unsigned int PPPOE_SES_HLEN ; 

__attribute__((used)) static unsigned int nf_bridge_mtu_reduction(const struct sk_buff *skb)
{
	if (skb->nf_bridge->orig_proto == BRNF_PROTO_PPPOE)
		return PPPOE_SES_HLEN;
	return 0;
}