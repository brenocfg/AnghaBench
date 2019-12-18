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
struct sk_buff {int dummy; } ;
struct nf_hook_state {int /*<<< orphan*/  pf; int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_ICMPV6 ; 
 int /*<<< orphan*/  nf_l4proto_log_invalid (struct sk_buff const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static void icmpv6_error_log(const struct sk_buff *skb,
			     const struct nf_hook_state *state,
			     const char *msg)
{
	nf_l4proto_log_invalid(skb, state->net, state->pf,
			       IPPROTO_ICMPV6, "%s", msg);
}