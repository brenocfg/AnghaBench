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
struct nf_hook_ops {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_nat_ipv6_ops ; 
 int /*<<< orphan*/  nf_nat_unregister_fn (struct net*,struct nf_hook_ops const*,int /*<<< orphan*/ ) ; 

void nf_nat_l3proto_ipv6_unregister_fn(struct net *net, const struct nf_hook_ops *ops)
{
	nf_nat_unregister_fn(net, ops, ARRAY_SIZE(nf_nat_ipv6_ops));
}