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
typedef  struct z_erofs_vle_workgroup* z_erofs_vle_owned_workgrp_t ;
struct z_erofs_vle_workgroup {struct z_erofs_vle_workgroup* next; } ;
typedef  enum z_erofs_vle_work_role { ____Placeholder_z_erofs_vle_work_role } z_erofs_vle_work_role ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_BUGON (int) ; 
 struct z_erofs_vle_workgroup* Z_EROFS_VLE_WORKGRP_NIL ; 
 struct z_erofs_vle_workgroup* Z_EROFS_VLE_WORKGRP_TAIL ; 
 int Z_EROFS_VLE_WORK_PRIMARY ; 
 int Z_EROFS_VLE_WORK_PRIMARY_FOLLOWED ; 
 int Z_EROFS_VLE_WORK_PRIMARY_HOOKED ; 
 struct z_erofs_vle_workgroup* cmpxchg (struct z_erofs_vle_workgroup**,struct z_erofs_vle_workgroup*,struct z_erofs_vle_workgroup*) ; 

__attribute__((used)) static enum z_erofs_vle_work_role
try_to_claim_workgroup(struct z_erofs_vle_workgroup *grp,
		       z_erofs_vle_owned_workgrp_t *owned_head,
		       bool *hosted)
{
	DBG_BUGON(*hosted == true);

	/* let's claim these following types of workgroup */
retry:
	if (grp->next == Z_EROFS_VLE_WORKGRP_NIL) {
		/* type 1, nil workgroup */
		if (Z_EROFS_VLE_WORKGRP_NIL != cmpxchg(&grp->next,
			Z_EROFS_VLE_WORKGRP_NIL, *owned_head))
			goto retry;

		*owned_head = grp;
		*hosted = true;
		/* lucky, I am the followee :) */
		return Z_EROFS_VLE_WORK_PRIMARY_FOLLOWED;

	} else if (grp->next == Z_EROFS_VLE_WORKGRP_TAIL) {
		/*
		 * type 2, link to the end of a existing open chain,
		 * be careful that its submission itself is governed
		 * by the original owned chain.
		 */
		if (Z_EROFS_VLE_WORKGRP_TAIL != cmpxchg(&grp->next,
			Z_EROFS_VLE_WORKGRP_TAIL, *owned_head))
			goto retry;
		*owned_head = Z_EROFS_VLE_WORKGRP_TAIL;
		return Z_EROFS_VLE_WORK_PRIMARY_HOOKED;
	}

	return Z_EROFS_VLE_WORK_PRIMARY; /* :( better luck next time */
}