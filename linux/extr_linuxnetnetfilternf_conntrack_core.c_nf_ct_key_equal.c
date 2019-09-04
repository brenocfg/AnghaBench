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
struct nf_conntrack_tuple_hash {int /*<<< orphan*/  tuple; } ;
struct nf_conntrack_tuple {int dummy; } ;
struct nf_conn {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NF_CT_DIRECTION (struct nf_conntrack_tuple_hash*) ; 
 scalar_t__ net_eq (struct net const*,int /*<<< orphan*/ ) ; 
 scalar_t__ nf_ct_is_confirmed (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_net (struct nf_conn*) ; 
 scalar_t__ nf_ct_tuple_equal (struct nf_conntrack_tuple const*,int /*<<< orphan*/ *) ; 
 struct nf_conn* nf_ct_tuplehash_to_ctrack (struct nf_conntrack_tuple_hash*) ; 
 scalar_t__ nf_ct_zone_equal (struct nf_conn*,struct nf_conntrack_zone const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
nf_ct_key_equal(struct nf_conntrack_tuple_hash *h,
		const struct nf_conntrack_tuple *tuple,
		const struct nf_conntrack_zone *zone,
		const struct net *net)
{
	struct nf_conn *ct = nf_ct_tuplehash_to_ctrack(h);

	/* A conntrack can be recreated with the equal tuple,
	 * so we need to check that the conntrack is confirmed
	 */
	return nf_ct_tuple_equal(tuple, &h->tuple) &&
	       nf_ct_zone_equal(ct, zone, NF_CT_DIRECTION(h)) &&
	       nf_ct_is_confirmed(ct) &&
	       net_eq(net, nf_ct_net(ct));
}