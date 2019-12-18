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
struct nf_conntrack_zone {int dummy; } ;
struct nf_conntrack_tuple_hash {int dummy; } ;
struct nf_conntrack_tuple {int dummy; } ;
struct TYPE_3__ {scalar_t__ stream_timeout; scalar_t__ timeout; } ;
struct TYPE_4__ {TYPE_1__ gre; } ;
struct nf_conntrack_expect {TYPE_2__ proto; } ;
struct nf_conn {TYPE_2__ proto; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct nf_conntrack_tuple_hash* nf_conntrack_find_get (struct net*,struct nf_conntrack_zone const*,struct nf_conntrack_tuple const*) ; 
 int /*<<< orphan*/  nf_ct_dump_tuple (struct nf_conntrack_tuple const*) ; 
 struct nf_conntrack_expect* nf_ct_expect_find_get (struct net*,struct nf_conntrack_zone const*,struct nf_conntrack_tuple const*) ; 
 int /*<<< orphan*/  nf_ct_expect_put (struct nf_conntrack_expect*) ; 
 int /*<<< orphan*/  nf_ct_kill (struct nf_conntrack_expect*) ; 
 int /*<<< orphan*/  nf_ct_put (struct nf_conntrack_expect*) ; 
 struct nf_conntrack_expect* nf_ct_tuplehash_to_ctrack (struct nf_conntrack_tuple_hash const*) ; 
 int /*<<< orphan*/  nf_ct_unexpect_related (struct nf_conntrack_expect*) ; 
 struct nf_conntrack_zone* nf_ct_zone (struct nf_conntrack_expect*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static int destroy_sibling_or_exp(struct net *net, struct nf_conn *ct,
				  const struct nf_conntrack_tuple *t)
{
	const struct nf_conntrack_tuple_hash *h;
	const struct nf_conntrack_zone *zone;
	struct nf_conntrack_expect *exp;
	struct nf_conn *sibling;

	pr_debug("trying to timeout ct or exp for tuple ");
	nf_ct_dump_tuple(t);

	zone = nf_ct_zone(ct);
	h = nf_conntrack_find_get(net, zone, t);
	if (h)  {
		sibling = nf_ct_tuplehash_to_ctrack(h);
		pr_debug("setting timeout of conntrack %p to 0\n", sibling);
		sibling->proto.gre.timeout	  = 0;
		sibling->proto.gre.stream_timeout = 0;
		nf_ct_kill(sibling);
		nf_ct_put(sibling);
		return 1;
	} else {
		exp = nf_ct_expect_find_get(net, zone, t);
		if (exp) {
			pr_debug("unexpect_related of expect %p\n", exp);
			nf_ct_unexpect_related(exp);
			nf_ct_expect_put(exp);
			return 1;
		}
	}
	return 0;
}