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
typedef  int /*<<< orphan*/  xfrm_address_t ;
struct xfrm_tmpl {unsigned short encap_family; } ;
struct xfrm_state_afinfo {int /*<<< orphan*/  (* init_temprop ) (struct xfrm_state*,struct xfrm_tmpl const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ;int /*<<< orphan*/  (* init_tempsel ) (int /*<<< orphan*/ *,struct flowi const*) ;} ;
struct xfrm_state {int /*<<< orphan*/  sel; } ;
struct flowi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct flowi const*) ; 
 int /*<<< orphan*/  stub2 (struct xfrm_state*,struct xfrm_tmpl const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 struct xfrm_state_afinfo* xfrm_state_afinfo_get_rcu (unsigned short) ; 

__attribute__((used)) static void
xfrm_init_tempstate(struct xfrm_state *x, const struct flowi *fl,
		    const struct xfrm_tmpl *tmpl,
		    const xfrm_address_t *daddr, const xfrm_address_t *saddr,
		    unsigned short family)
{
	struct xfrm_state_afinfo *afinfo = xfrm_state_afinfo_get_rcu(family);

	if (!afinfo)
		return;

	afinfo->init_tempsel(&x->sel, fl);

	if (family != tmpl->encap_family) {
		afinfo = xfrm_state_afinfo_get_rcu(tmpl->encap_family);
		if (!afinfo)
			return;
	}
	afinfo->init_temprop(x, tmpl, daddr, saddr);
}