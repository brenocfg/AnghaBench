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
struct xfrm_user_tmpl {int /*<<< orphan*/  calgos; int /*<<< orphan*/  ealgos; int /*<<< orphan*/  aalgos; int /*<<< orphan*/  optional; int /*<<< orphan*/  share; int /*<<< orphan*/  mode; int /*<<< orphan*/  reqid; int /*<<< orphan*/  saddr; int /*<<< orphan*/  family; int /*<<< orphan*/  id; } ;
struct xfrm_tmpl {int /*<<< orphan*/  calgos; int /*<<< orphan*/  ealgos; int /*<<< orphan*/  aalgos; int /*<<< orphan*/  optional; int /*<<< orphan*/  share; int /*<<< orphan*/  mode; int /*<<< orphan*/  reqid; int /*<<< orphan*/  saddr; int /*<<< orphan*/  encap_family; int /*<<< orphan*/  id; } ;
struct xfrm_policy {int xfrm_nr; struct xfrm_tmpl* xfrm_vec; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFRMA_TMPL ; 
 int XFRM_MAX_DEPTH ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct xfrm_user_tmpl*,int /*<<< orphan*/ ,int) ; 
 int nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct xfrm_user_tmpl*) ; 

__attribute__((used)) static int copy_to_user_tmpl(struct xfrm_policy *xp, struct sk_buff *skb)
{
	struct xfrm_user_tmpl vec[XFRM_MAX_DEPTH];
	int i;

	if (xp->xfrm_nr == 0)
		return 0;

	for (i = 0; i < xp->xfrm_nr; i++) {
		struct xfrm_user_tmpl *up = &vec[i];
		struct xfrm_tmpl *kp = &xp->xfrm_vec[i];

		memset(up, 0, sizeof(*up));
		memcpy(&up->id, &kp->id, sizeof(up->id));
		up->family = kp->encap_family;
		memcpy(&up->saddr, &kp->saddr, sizeof(up->saddr));
		up->reqid = kp->reqid;
		up->mode = kp->mode;
		up->share = kp->share;
		up->optional = kp->optional;
		up->aalgos = kp->aalgos;
		up->ealgos = kp->ealgos;
		up->calgos = kp->calgos;
	}

	return nla_put(skb, XFRMA_TMPL,
		       sizeof(struct xfrm_user_tmpl) * xp->xfrm_nr, vec);
}