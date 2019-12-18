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
typedef  int /*<<< orphan*/  xfrm_address_t ;
typedef  int /*<<< orphan*/  u16 ;
struct xfrm_pol_inexact_node {int /*<<< orphan*/  hhead; int /*<<< orphan*/  root; } ;
struct xfrm_pol_inexact_candidates {int /*<<< orphan*/ ** res; } ;
struct TYPE_2__ {int /*<<< orphan*/  family; } ;
struct xfrm_pol_inexact_bin {int /*<<< orphan*/  count; int /*<<< orphan*/  root_s; int /*<<< orphan*/  root_d; int /*<<< orphan*/  hhead; TYPE_1__ k; } ;

/* Variables and functions */
 size_t XFRM_POL_CAND_ANY ; 
 size_t XFRM_POL_CAND_BOTH ; 
 size_t XFRM_POL_CAND_DADDR ; 
 size_t XFRM_POL_CAND_SADDR ; 
 int /*<<< orphan*/  memset (struct xfrm_pol_inexact_candidates*,int /*<<< orphan*/ ,int) ; 
 struct xfrm_pol_inexact_node* xfrm_policy_lookup_inexact_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
xfrm_policy_find_inexact_candidates(struct xfrm_pol_inexact_candidates *cand,
				    struct xfrm_pol_inexact_bin *b,
				    const xfrm_address_t *saddr,
				    const xfrm_address_t *daddr)
{
	struct xfrm_pol_inexact_node *n;
	u16 family;

	if (!b)
		return false;

	family = b->k.family;
	memset(cand, 0, sizeof(*cand));
	cand->res[XFRM_POL_CAND_ANY] = &b->hhead;

	n = xfrm_policy_lookup_inexact_addr(&b->root_d, &b->count, daddr,
					    family);
	if (n) {
		cand->res[XFRM_POL_CAND_DADDR] = &n->hhead;
		n = xfrm_policy_lookup_inexact_addr(&n->root, &b->count, saddr,
						    family);
		if (n)
			cand->res[XFRM_POL_CAND_BOTH] = &n->hhead;
	}

	n = xfrm_policy_lookup_inexact_addr(&b->root_s, &b->count, saddr,
					    family);
	if (n)
		cand->res[XFRM_POL_CAND_SADDR] = &n->hhead;

	return true;
}