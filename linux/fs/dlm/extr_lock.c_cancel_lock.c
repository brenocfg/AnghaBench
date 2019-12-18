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
struct dlm_rsb {int dummy; } ;
struct dlm_ls {int dummy; } ;
struct dlm_lkb {struct dlm_rsb* lkb_resource; } ;
struct dlm_args {int dummy; } ;

/* Variables and functions */
 int _cancel_lock (struct dlm_rsb*,struct dlm_lkb*) ; 
 int /*<<< orphan*/  hold_rsb (struct dlm_rsb*) ; 
 int /*<<< orphan*/  lock_rsb (struct dlm_rsb*) ; 
 int /*<<< orphan*/  put_rsb (struct dlm_rsb*) ; 
 int /*<<< orphan*/  unlock_rsb (struct dlm_rsb*) ; 
 int validate_unlock_args (struct dlm_lkb*,struct dlm_args*) ; 

__attribute__((used)) static int cancel_lock(struct dlm_ls *ls, struct dlm_lkb *lkb,
		       struct dlm_args *args)
{
	struct dlm_rsb *r;
	int error;

	r = lkb->lkb_resource;

	hold_rsb(r);
	lock_rsb(r);

	error = validate_unlock_args(lkb, args);
	if (error)
		goto out;

	error = _cancel_lock(r, lkb);
 out:
	unlock_rsb(r);
	put_rsb(r);
	return error;
}