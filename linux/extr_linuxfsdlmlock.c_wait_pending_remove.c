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
struct dlm_rsb {int /*<<< orphan*/  res_name; int /*<<< orphan*/  res_dir_nodeid; struct dlm_ls* res_ls; } ;
struct dlm_ls {int /*<<< orphan*/  ls_remove_spin; scalar_t__ ls_remove_len; int /*<<< orphan*/  ls_remove_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  log_debug (struct dlm_ls*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rsb_cmp (struct dlm_rsb*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wait_pending_remove(struct dlm_rsb *r)
{
	struct dlm_ls *ls = r->res_ls;
 restart:
	spin_lock(&ls->ls_remove_spin);
	if (ls->ls_remove_len &&
	    !rsb_cmp(r, ls->ls_remove_name, ls->ls_remove_len)) {
		log_debug(ls, "delay lookup for remove dir %d %s",
		  	  r->res_dir_nodeid, r->res_name);
		spin_unlock(&ls->ls_remove_spin);
		msleep(1);
		goto restart;
	}
	spin_unlock(&ls->ls_remove_spin);
}