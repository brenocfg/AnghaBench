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
struct dlm_rsb {int dummy; } ;
struct dlm_ls {int dummy; } ;
struct dlm_lkb {int /*<<< orphan*/  lkb_id; TYPE_1__* lkb_lksb; } ;
struct dlm_args {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sb_lkid; } ;

/* Variables and functions */
 int /*<<< orphan*/  R_REQUEST ; 
 int _request_lock (struct dlm_rsb*,struct dlm_lkb*) ; 
 int /*<<< orphan*/  attach_lkb (struct dlm_rsb*,struct dlm_lkb*) ; 
 int find_rsb (struct dlm_ls*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dlm_rsb**) ; 
 int /*<<< orphan*/  lock_rsb (struct dlm_rsb*) ; 
 int /*<<< orphan*/  put_rsb (struct dlm_rsb*) ; 
 int /*<<< orphan*/  unlock_rsb (struct dlm_rsb*) ; 
 int validate_lock_args (struct dlm_ls*,struct dlm_lkb*,struct dlm_args*) ; 

__attribute__((used)) static int request_lock(struct dlm_ls *ls, struct dlm_lkb *lkb, char *name,
			int len, struct dlm_args *args)
{
	struct dlm_rsb *r;
	int error;

	error = validate_lock_args(ls, lkb, args);
	if (error)
		return error;

	error = find_rsb(ls, name, len, 0, R_REQUEST, &r);
	if (error)
		return error;

	lock_rsb(r);

	attach_lkb(r, lkb);
	lkb->lkb_lksb->sb_lkid = lkb->lkb_id;

	error = _request_lock(r, lkb);

	unlock_rsb(r);
	put_rsb(r);
	return error;
}