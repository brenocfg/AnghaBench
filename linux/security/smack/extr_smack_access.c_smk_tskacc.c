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
typedef  int u32 ;
struct task_smack {int /*<<< orphan*/  smk_rules; } ;
struct smk_audit_info {int dummy; } ;
struct smack_known {int /*<<< orphan*/  smk_known; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_MAC_OVERRIDE ; 
 int EACCES ; 
 int /*<<< orphan*/  smack_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct smk_audit_info*) ; 
 scalar_t__ smack_privileged (int /*<<< orphan*/ ) ; 
 int smk_access (struct smack_known*,struct smack_known*,int,int /*<<< orphan*/ *) ; 
 int smk_access_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct smack_known* smk_of_task (struct task_smack*) ; 

int smk_tskacc(struct task_smack *tsp, struct smack_known *obj_known,
	       u32 mode, struct smk_audit_info *a)
{
	struct smack_known *sbj_known = smk_of_task(tsp);
	int may;
	int rc;

	/*
	 * Check the global rule list
	 */
	rc = smk_access(sbj_known, obj_known, mode, NULL);
	if (rc >= 0) {
		/*
		 * If there is an entry in the task's rule list
		 * it can further restrict access.
		 */
		may = smk_access_entry(sbj_known->smk_known,
				       obj_known->smk_known,
				       &tsp->smk_rules);
		if (may < 0)
			goto out_audit;
		if ((mode & may) == mode)
			goto out_audit;
		rc = -EACCES;
	}

	/*
	 * Allow for priviliged to override policy.
	 */
	if (rc != 0 && smack_privileged(CAP_MAC_OVERRIDE))
		rc = 0;

out_audit:
#ifdef CONFIG_AUDIT
	if (a)
		smack_log(sbj_known->smk_known, obj_known->smk_known,
			  mode, rc, a);
#endif
	return rc;
}