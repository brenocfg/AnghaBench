#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  fl_pid; int /*<<< orphan*/  fl_type; int /*<<< orphan*/  fl_end; int /*<<< orphan*/  fl_start; } ;
struct TYPE_5__ {TYPE_1__ fl; } ;
struct TYPE_6__ {int status; TYPE_2__ lock; } ;
struct nlm_rqst {TYPE_3__ a_res; } ;
struct file_lock {int /*<<< orphan*/  fl_pid; int /*<<< orphan*/  fl_type; int /*<<< orphan*/  fl_end; int /*<<< orphan*/  fl_start; int /*<<< orphan*/  fl_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_UNLCK ; 
 int /*<<< orphan*/  NLMPROC_TEST ; 
 int /*<<< orphan*/  nfs_file_cred (int /*<<< orphan*/ ) ; 
#define  nlm_granted 129 
#define  nlm_lck_denied 128 
 int nlm_stat_to_errno (int) ; 
 int nlmclnt_call (int /*<<< orphan*/ ,struct nlm_rqst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmclnt_release_call (struct nlm_rqst*) ; 

__attribute__((used)) static int
nlmclnt_test(struct nlm_rqst *req, struct file_lock *fl)
{
	int	status;

	status = nlmclnt_call(nfs_file_cred(fl->fl_file), req, NLMPROC_TEST);
	if (status < 0)
		goto out;

	switch (req->a_res.status) {
		case nlm_granted:
			fl->fl_type = F_UNLCK;
			break;
		case nlm_lck_denied:
			/*
			 * Report the conflicting lock back to the application.
			 */
			fl->fl_start = req->a_res.lock.fl.fl_start;
			fl->fl_end = req->a_res.lock.fl.fl_end;
			fl->fl_type = req->a_res.lock.fl.fl_type;
			fl->fl_pid = -req->a_res.lock.fl.fl_pid;
			break;
		default:
			status = nlm_stat_to_errno(req->a_res.status);
	}
out:
	nlmclnt_release_call(req);
	return status;
}