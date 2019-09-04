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
struct sk_buff {int dummy; } ;
struct nf_hook_state {scalar_t__ hook; TYPE_2__* net; } ;
struct TYPE_3__ {int /*<<< orphan*/  iptable_mangle; } ;
struct TYPE_4__ {TYPE_1__ ipv4; } ;

/* Variables and functions */
 scalar_t__ NF_INET_LOCAL_OUT ; 
 unsigned int ipt_do_table (struct sk_buff*,struct nf_hook_state const*,int /*<<< orphan*/ ) ; 
 unsigned int ipt_mangle_out (struct sk_buff*,struct nf_hook_state const*) ; 

__attribute__((used)) static unsigned int
iptable_mangle_hook(void *priv,
		     struct sk_buff *skb,
		     const struct nf_hook_state *state)
{
	if (state->hook == NF_INET_LOCAL_OUT)
		return ipt_mangle_out(skb, state);
	return ipt_do_table(skb, state, state->net->ipv4.iptable_mangle);
}