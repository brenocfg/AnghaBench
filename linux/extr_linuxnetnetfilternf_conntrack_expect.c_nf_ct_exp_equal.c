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
struct nf_conntrack_zone {int dummy; } ;
struct nf_conntrack_tuple {int dummy; } ;
struct nf_conntrack_expect {int /*<<< orphan*/  master; int /*<<< orphan*/  mask; int /*<<< orphan*/  tuple; } ;
struct net {int dummy; } ;

/* Variables and functions */
 scalar_t__ net_eq (struct net const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_net (int /*<<< orphan*/ ) ; 
 scalar_t__ nf_ct_tuple_mask_cmp (struct nf_conntrack_tuple const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ nf_ct_zone_equal_any (int /*<<< orphan*/ ,struct nf_conntrack_zone const*) ; 

__attribute__((used)) static bool
nf_ct_exp_equal(const struct nf_conntrack_tuple *tuple,
		const struct nf_conntrack_expect *i,
		const struct nf_conntrack_zone *zone,
		const struct net *net)
{
	return nf_ct_tuple_mask_cmp(tuple, &i->tuple, &i->mask) &&
	       net_eq(net, nf_ct_net(i->master)) &&
	       nf_ct_zone_equal_any(i->master, zone);
}