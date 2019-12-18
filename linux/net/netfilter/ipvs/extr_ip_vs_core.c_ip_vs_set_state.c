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
struct ip_vs_proto_data {TYPE_1__* pp; } ;
struct ip_vs_conn {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* state_transition ) (struct ip_vs_conn*,int,struct sk_buff const*,struct ip_vs_proto_data*) ;} ;

/* Variables and functions */
 scalar_t__ likely (int /*<<< orphan*/  (*) (struct ip_vs_conn*,int,struct sk_buff const*,struct ip_vs_proto_data*)) ; 
 int /*<<< orphan*/  stub1 (struct ip_vs_conn*,int,struct sk_buff const*,struct ip_vs_proto_data*) ; 

__attribute__((used)) static inline void
ip_vs_set_state(struct ip_vs_conn *cp, int direction,
		const struct sk_buff *skb,
		struct ip_vs_proto_data *pd)
{
	if (likely(pd->pp->state_transition))
		pd->pp->state_transition(cp, direction, skb, pd);
}