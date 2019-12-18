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
struct TYPE_2__ {int /*<<< orphan*/  family; } ;
struct xfrm_userpolicy_info {int dir; int /*<<< orphan*/  share; int /*<<< orphan*/  flags; int /*<<< orphan*/  action; TYPE_1__ sel; int /*<<< orphan*/  index; int /*<<< orphan*/  priority; TYPE_1__ curlft; TYPE_1__ lft; } ;
struct xfrm_policy {int /*<<< orphan*/  flags; int /*<<< orphan*/  action; int /*<<< orphan*/  family; int /*<<< orphan*/  index; int /*<<< orphan*/  priority; int /*<<< orphan*/  curlft; int /*<<< orphan*/  lft; int /*<<< orphan*/  selector; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFRM_SHARE_ANY ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct xfrm_userpolicy_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void copy_to_user_policy(struct xfrm_policy *xp, struct xfrm_userpolicy_info *p, int dir)
{
	memset(p, 0, sizeof(*p));
	memcpy(&p->sel, &xp->selector, sizeof(p->sel));
	memcpy(&p->lft, &xp->lft, sizeof(p->lft));
	memcpy(&p->curlft, &xp->curlft, sizeof(p->curlft));
	p->priority = xp->priority;
	p->index = xp->index;
	p->sel.family = xp->family;
	p->dir = dir;
	p->action = xp->action;
	p->flags = xp->flags;
	p->share = XFRM_SHARE_ANY; /* XXX xp->share */
}