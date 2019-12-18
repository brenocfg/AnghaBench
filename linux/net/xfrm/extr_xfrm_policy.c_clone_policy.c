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
struct xfrm_tmpl {int dummy; } ;
struct xfrm_policy {int xfrm_nr; int /*<<< orphan*/  xfrm_vec; int /*<<< orphan*/  family; int /*<<< orphan*/  type; int /*<<< orphan*/  index; int /*<<< orphan*/  flags; int /*<<< orphan*/  action; int /*<<< orphan*/  if_id; int /*<<< orphan*/  mark; int /*<<< orphan*/  curlft; int /*<<< orphan*/  lft; int /*<<< orphan*/  security; int /*<<< orphan*/  selector; } ;
struct TYPE_2__ {int /*<<< orphan*/  xfrm_policy_lock; } ;
struct net {TYPE_1__ xfrm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kfree (struct xfrm_policy*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ security_xfrm_policy_clone (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfrm_pol_put (struct xfrm_policy*) ; 
 struct xfrm_policy* xfrm_policy_alloc (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_sk_policy_link (struct xfrm_policy*,int) ; 
 struct net* xp_net (struct xfrm_policy const*) ; 

__attribute__((used)) static struct xfrm_policy *clone_policy(const struct xfrm_policy *old, int dir)
{
	struct xfrm_policy *newp = xfrm_policy_alloc(xp_net(old), GFP_ATOMIC);
	struct net *net = xp_net(old);

	if (newp) {
		newp->selector = old->selector;
		if (security_xfrm_policy_clone(old->security,
					       &newp->security)) {
			kfree(newp);
			return NULL;  /* ENOMEM */
		}
		newp->lft = old->lft;
		newp->curlft = old->curlft;
		newp->mark = old->mark;
		newp->if_id = old->if_id;
		newp->action = old->action;
		newp->flags = old->flags;
		newp->xfrm_nr = old->xfrm_nr;
		newp->index = old->index;
		newp->type = old->type;
		newp->family = old->family;
		memcpy(newp->xfrm_vec, old->xfrm_vec,
		       newp->xfrm_nr*sizeof(struct xfrm_tmpl));
		spin_lock_bh(&net->xfrm.xfrm_policy_lock);
		xfrm_sk_policy_link(newp, dir);
		spin_unlock_bh(&net->xfrm.xfrm_policy_lock);
		xfrm_pol_put(newp);
	}
	return newp;
}