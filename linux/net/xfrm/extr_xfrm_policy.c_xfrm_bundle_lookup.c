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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct xfrm_policy {int dummy; } ;
struct xfrm_flo {int /*<<< orphan*/  dst_orig; } ;
struct xfrm_dst {int num_pols; int num_xfrms; int /*<<< orphan*/  pols; } ;
struct net {int dummy; } ;
struct flowi {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EREMOTE ; 
 struct xfrm_dst* ERR_CAST (struct xfrm_dst*) ; 
 struct xfrm_dst* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct xfrm_dst*) ; 
 int /*<<< orphan*/  LINUX_MIB_XFRMOUTPOLERROR ; 
 int PTR_ERR (struct xfrm_dst*) ; 
 int /*<<< orphan*/  XFRM_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 int XFRM_POLICY_TYPE_MAX ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct xfrm_policy**,int) ; 
 struct xfrm_dst* xfrm_create_dummy_bundle (struct net*,struct xfrm_flo*,struct flowi const*,int,int /*<<< orphan*/ ) ; 
 int xfrm_expand_policies (struct flowi const*,int /*<<< orphan*/ ,struct xfrm_policy**,int*,int*) ; 
 struct xfrm_policy* xfrm_policy_lookup (struct net*,struct flowi const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_pols_put (struct xfrm_policy**,int) ; 
 struct xfrm_dst* xfrm_resolve_and_create_bundle (struct xfrm_policy**,int,struct flowi const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct xfrm_dst *xfrm_bundle_lookup(struct net *net,
					   const struct flowi *fl,
					   u16 family, u8 dir,
					   struct xfrm_flo *xflo, u32 if_id)
{
	struct xfrm_policy *pols[XFRM_POLICY_TYPE_MAX];
	int num_pols = 0, num_xfrms = 0, err;
	struct xfrm_dst *xdst;

	/* Resolve policies to use if we couldn't get them from
	 * previous cache entry */
	num_pols = 1;
	pols[0] = xfrm_policy_lookup(net, fl, family, dir, if_id);
	err = xfrm_expand_policies(fl, family, pols,
					   &num_pols, &num_xfrms);
	if (err < 0)
		goto inc_error;
	if (num_pols == 0)
		return NULL;
	if (num_xfrms <= 0)
		goto make_dummy_bundle;

	xdst = xfrm_resolve_and_create_bundle(pols, num_pols, fl, family,
					      xflo->dst_orig);
	if (IS_ERR(xdst)) {
		err = PTR_ERR(xdst);
		if (err == -EREMOTE) {
			xfrm_pols_put(pols, num_pols);
			return NULL;
		}

		if (err != -EAGAIN)
			goto error;
		goto make_dummy_bundle;
	} else if (xdst == NULL) {
		num_xfrms = 0;
		goto make_dummy_bundle;
	}

	return xdst;

make_dummy_bundle:
	/* We found policies, but there's no bundles to instantiate:
	 * either because the policy blocks, has no transformations or
	 * we could not build template (no xfrm_states).*/
	xdst = xfrm_create_dummy_bundle(net, xflo, fl, num_xfrms, family);
	if (IS_ERR(xdst)) {
		xfrm_pols_put(pols, num_pols);
		return ERR_CAST(xdst);
	}
	xdst->num_pols = num_pols;
	xdst->num_xfrms = num_xfrms;
	memcpy(xdst->pols, pols, sizeof(struct xfrm_policy *) * num_pols);

	return xdst;

inc_error:
	XFRM_INC_STATS(net, LINUX_MIB_XFRMOUTPOLERROR);
error:
	xfrm_pols_put(pols, num_pols);
	return ERR_PTR(err);
}