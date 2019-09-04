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
struct xfrm_user_tmpl {int aalgos; int ealgos; int calgos; int /*<<< orphan*/  family; int /*<<< orphan*/  optional; int /*<<< orphan*/  share; int /*<<< orphan*/  mode; int /*<<< orphan*/  reqid; int /*<<< orphan*/  saddr; int /*<<< orphan*/  id; } ;
struct xfrm_tmpl {int aalgos; int ealgos; int calgos; int allalgs; int /*<<< orphan*/  encap_family; int /*<<< orphan*/  optional; int /*<<< orphan*/  share; int /*<<< orphan*/  mode; int /*<<< orphan*/  reqid; int /*<<< orphan*/  saddr; int /*<<< orphan*/  id; } ;
struct xfrm_policy {int xfrm_nr; struct xfrm_tmpl* xfrm_vec; } ;
struct xfrm_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void copy_templates(struct xfrm_policy *xp, struct xfrm_user_tmpl *ut,
			   int nr)
{
	int i;

	xp->xfrm_nr = nr;
	for (i = 0; i < nr; i++, ut++) {
		struct xfrm_tmpl *t = &xp->xfrm_vec[i];

		memcpy(&t->id, &ut->id, sizeof(struct xfrm_id));
		memcpy(&t->saddr, &ut->saddr,
		       sizeof(xfrm_address_t));
		t->reqid = ut->reqid;
		t->mode = ut->mode;
		t->share = ut->share;
		t->optional = ut->optional;
		t->aalgos = ut->aalgos;
		t->ealgos = ut->ealgos;
		t->calgos = ut->calgos;
		/* If all masks are ~0, then we allow all algorithms. */
		t->allalgs = !~(t->aalgos & t->ealgos & t->calgos);
		t->encap_family = ut->family;
	}
}