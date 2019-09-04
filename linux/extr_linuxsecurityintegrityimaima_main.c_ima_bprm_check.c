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
typedef  int /*<<< orphan*/  u32 ;
struct linux_binprm {int /*<<< orphan*/  cred; int /*<<< orphan*/  file; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPRM_CHECK ; 
 int /*<<< orphan*/  CREDS_CHECK ; 
 int /*<<< orphan*/  MAY_EXEC ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  current_cred () ; 
 int process_measurement (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  security_cred_getsecid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  security_task_getsecid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ima_bprm_check(struct linux_binprm *bprm)
{
	int ret;
	u32 secid;

	security_task_getsecid(current, &secid);
	ret = process_measurement(bprm->file, current_cred(), secid, NULL, 0,
				  MAY_EXEC, BPRM_CHECK);
	if (ret)
		return ret;

	security_cred_getsecid(bprm->cred, &secid);
	return process_measurement(bprm->file, bprm->cred, secid, NULL, 0,
				   MAY_EXEC, CREDS_CHECK);
}