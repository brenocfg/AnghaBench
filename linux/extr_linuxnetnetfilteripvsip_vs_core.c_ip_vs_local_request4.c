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
struct nf_hook_state {int /*<<< orphan*/  hook; int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 unsigned int ip_vs_in (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_ipvs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
ip_vs_local_request4(void *priv, struct sk_buff *skb,
		     const struct nf_hook_state *state)
{
	return ip_vs_in(net_ipvs(state->net), state->hook, skb, AF_INET);
}