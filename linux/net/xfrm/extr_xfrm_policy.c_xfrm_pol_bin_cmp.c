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
struct xfrm_pol_inexact_key {int dir; int type; int family; int if_id; int /*<<< orphan*/  net; } ;
struct TYPE_2__ {int dir; int type; int family; int if_id; int /*<<< orphan*/  net; } ;
struct xfrm_pol_inexact_bin {TYPE_1__ k; } ;
struct rhashtable_compare_arg {struct xfrm_pol_inexact_key* key; } ;

/* Variables and functions */
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_pnet (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int xfrm_pol_bin_cmp(struct rhashtable_compare_arg *arg,
			    const void *ptr)
{
	const struct xfrm_pol_inexact_key *key = arg->key;
	const struct xfrm_pol_inexact_bin *b = ptr;
	int ret;

	if (!net_eq(read_pnet(&b->k.net), read_pnet(&key->net)))
		return -1;

	ret = b->k.dir ^ key->dir;
	if (ret)
		return ret;

	ret = b->k.type ^ key->type;
	if (ret)
		return ret;

	ret = b->k.family ^ key->family;
	if (ret)
		return ret;

	return b->k.if_id ^ key->if_id;
}