#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct flow_keys {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  all; } ;
struct TYPE_4__ {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTTUPLE (struct sk_buff const*,int /*<<< orphan*/ ) ; 
 TYPE_2__ dst ; 
 int /*<<< orphan*/  flow_get_proto_dst (struct sk_buff const*,struct flow_keys const*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 flow_get_nfct_proto_dst(const struct sk_buff *skb,
				   const struct flow_keys *flow)
{
	return ntohs(CTTUPLE(skb, dst.u.all));
fallback:
	return flow_get_proto_dst(skb, flow);
}