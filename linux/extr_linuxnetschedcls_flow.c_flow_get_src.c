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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct flow_keys {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  addr_fold (int /*<<< orphan*/ ) ; 
 scalar_t__ flow_get_u32_src (struct flow_keys const*) ; 
 int /*<<< orphan*/  ntohl (scalar_t__) ; 

__attribute__((used)) static u32 flow_get_src(const struct sk_buff *skb, const struct flow_keys *flow)
{
	__be32 src = flow_get_u32_src(flow);

	if (src)
		return ntohl(src);

	return addr_fold(skb->sk);
}