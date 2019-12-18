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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct TYPE_2__ {int /*<<< orphan*/  src; scalar_t__ ports; } ;
struct flow_keys {TYPE_1__ ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  addr_fold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 flow_get_proto_src(const struct sk_buff *skb,
			      const struct flow_keys *flow)
{
	if (flow->ports.ports)
		return ntohs(flow->ports.src);

	return addr_fold(skb->sk);
}