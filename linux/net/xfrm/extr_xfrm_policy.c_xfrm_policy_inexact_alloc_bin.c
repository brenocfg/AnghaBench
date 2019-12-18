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
typedef  int /*<<< orphan*/  u8 ;
struct xfrm_policy {int /*<<< orphan*/  if_id; int /*<<< orphan*/  type; int /*<<< orphan*/  family; } ;
struct xfrm_pol_inexact_key {int /*<<< orphan*/  net; int /*<<< orphan*/  if_id; int /*<<< orphan*/  dir; int /*<<< orphan*/  type; int /*<<< orphan*/  family; } ;
struct xfrm_pol_inexact_bin {int /*<<< orphan*/  inexact_bins; int /*<<< orphan*/  head; struct xfrm_pol_inexact_key k; int /*<<< orphan*/  count; void* root_s; void* root_d; int /*<<< orphan*/  hhead; } ;
struct TYPE_2__ {int /*<<< orphan*/  inexact_bins; int /*<<< orphan*/  xfrm_policy_lock; } ;
struct net {TYPE_1__ xfrm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct xfrm_pol_inexact_bin*) ; 
 void* RB_ROOT ; 
 int /*<<< orphan*/  kfree (struct xfrm_pol_inexact_bin*) ; 
 struct xfrm_pol_inexact_bin* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 struct xfrm_pol_inexact_bin* rhashtable_lookup_fast (int /*<<< orphan*/ *,struct xfrm_pol_inexact_key*,int /*<<< orphan*/ ) ; 
 struct xfrm_pol_inexact_bin* rhashtable_lookup_get_insert_key (int /*<<< orphan*/ *,struct xfrm_pol_inexact_key*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seqcount_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_pnet (int /*<<< orphan*/ *,struct net*) ; 
 int /*<<< orphan*/  xfrm_pol_inexact_params ; 
 int /*<<< orphan*/  xfrm_policy_inexact_table ; 
 struct net* xp_net (struct xfrm_policy const*) ; 

__attribute__((used)) static struct xfrm_pol_inexact_bin *
xfrm_policy_inexact_alloc_bin(const struct xfrm_policy *pol, u8 dir)
{
	struct xfrm_pol_inexact_bin *bin, *prev;
	struct xfrm_pol_inexact_key k = {
		.family = pol->family,
		.type = pol->type,
		.dir = dir,
		.if_id = pol->if_id,
	};
	struct net *net = xp_net(pol);

	lockdep_assert_held(&net->xfrm.xfrm_policy_lock);

	write_pnet(&k.net, net);
	bin = rhashtable_lookup_fast(&xfrm_policy_inexact_table, &k,
				     xfrm_pol_inexact_params);
	if (bin)
		return bin;

	bin = kzalloc(sizeof(*bin), GFP_ATOMIC);
	if (!bin)
		return NULL;

	bin->k = k;
	INIT_HLIST_HEAD(&bin->hhead);
	bin->root_d = RB_ROOT;
	bin->root_s = RB_ROOT;
	seqcount_init(&bin->count);

	prev = rhashtable_lookup_get_insert_key(&xfrm_policy_inexact_table,
						&bin->k, &bin->head,
						xfrm_pol_inexact_params);
	if (!prev) {
		list_add(&bin->inexact_bins, &net->xfrm.inexact_bins);
		return bin;
	}

	kfree(bin);

	return IS_ERR(prev) ? NULL : prev;
}