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
struct net_bridge_port {int flags; } ;
struct TYPE_2__ {scalar_t__ src_port_isolated; } ;

/* Variables and functions */
 TYPE_1__* BR_INPUT_SKB_CB (struct sk_buff const*) ; 
 int BR_ISOLATED ; 

__attribute__((used)) static inline bool br_skb_isolated(const struct net_bridge_port *to,
				   const struct sk_buff *skb)
{
	return BR_INPUT_SKB_CB(skb)->src_port_isolated &&
	       (to->flags & BR_ISOLATED);
}