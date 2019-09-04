#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ tsk; } ;
struct common_audit_data {scalar_t__ type; TYPE_1__ u; } ;
struct aa_profile {int /*<<< orphan*/  label; } ;
struct TYPE_4__ {int error; int type; int /*<<< orphan*/ * label; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 scalar_t__ AUDIT_ALL ; 
 int AUDIT_APPARMOR_ALLOWED ; 
 int AUDIT_APPARMOR_AUDIT ; 
 int AUDIT_APPARMOR_AUTO ; 
 int AUDIT_APPARMOR_DENIED ; 
 int AUDIT_APPARMOR_KILL ; 
 scalar_t__ AUDIT_MODE (struct aa_profile*) ; 
 scalar_t__ AUDIT_QUIET ; 
 scalar_t__ COMPLAIN_MODE (struct aa_profile*) ; 
 scalar_t__ KILL_MODE (struct aa_profile*) ; 
 scalar_t__ LSM_AUDIT_DATA_TASK ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  aa_audit_msg (int,struct common_audit_data*,void (*) (struct audit_buffer*,void*)) ; 
 TYPE_2__* aad (struct common_audit_data*) ; 
 int complain_error (int) ; 
 scalar_t__ current ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  send_sig_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

int aa_audit(int type, struct aa_profile *profile, struct common_audit_data *sa,
	     void (*cb) (struct audit_buffer *, void *))
{
	AA_BUG(!profile);

	if (type == AUDIT_APPARMOR_AUTO) {
		if (likely(!aad(sa)->error)) {
			if (AUDIT_MODE(profile) != AUDIT_ALL)
				return 0;
			type = AUDIT_APPARMOR_AUDIT;
		} else if (COMPLAIN_MODE(profile))
			type = AUDIT_APPARMOR_ALLOWED;
		else
			type = AUDIT_APPARMOR_DENIED;
	}
	if (AUDIT_MODE(profile) == AUDIT_QUIET ||
	    (type == AUDIT_APPARMOR_DENIED &&
	     AUDIT_MODE(profile) == AUDIT_QUIET))
		return aad(sa)->error;

	if (KILL_MODE(profile) && type == AUDIT_APPARMOR_DENIED)
		type = AUDIT_APPARMOR_KILL;

	aad(sa)->label = &profile->label;

	aa_audit_msg(type, sa, cb);

	if (aad(sa)->type == AUDIT_APPARMOR_KILL)
		(void)send_sig_info(SIGKILL, NULL,
			sa->type == LSM_AUDIT_DATA_TASK && sa->u.tsk ?
				    sa->u.tsk : current);

	if (aad(sa)->type == AUDIT_APPARMOR_ALLOWED)
		return complain_error(aad(sa)->error);

	return aad(sa)->error;
}