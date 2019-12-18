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
struct dlm_ls {int ls_rsbtbl_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  RSB_RECOVER_GRANT ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  confirm_master (struct dlm_rsb*,int /*<<< orphan*/ ) ; 
 struct dlm_rsb* find_grant_rsb (struct dlm_ls*,int) ; 
 int /*<<< orphan*/  grant_pending_locks (struct dlm_rsb*,unsigned int*) ; 
 int /*<<< orphan*/  lock_rsb (struct dlm_rsb*) ; 
 int /*<<< orphan*/  log_rinfo (struct dlm_ls*,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  put_rsb (struct dlm_rsb*) ; 
 int /*<<< orphan*/  rsb_clear_flag (struct dlm_rsb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_rsb (struct dlm_rsb*) ; 

void dlm_recover_grant(struct dlm_ls *ls)
{
	struct dlm_rsb *r;
	int bucket = 0;
	unsigned int count = 0;
	unsigned int rsb_count = 0;
	unsigned int lkb_count = 0;

	while (1) {
		r = find_grant_rsb(ls, bucket);
		if (!r) {
			if (bucket == ls->ls_rsbtbl_size - 1)
				break;
			bucket++;
			continue;
		}
		rsb_count++;
		count = 0;
		lock_rsb(r);
		/* the RECOVER_GRANT flag is checked in the grant path */
		grant_pending_locks(r, &count);
		rsb_clear_flag(r, RSB_RECOVER_GRANT);
		lkb_count += count;
		confirm_master(r, 0);
		unlock_rsb(r);
		put_rsb(r);
		cond_resched();
	}

	if (lkb_count)
		log_rinfo(ls, "dlm_recover_grant %u locks on %u resources",
			  lkb_count, rsb_count);
}