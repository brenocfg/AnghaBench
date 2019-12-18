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
struct task_smack {int dummy; } ;
struct smk_audit_info {int dummy; } ;
struct smack_known {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_cred () ; 
 struct task_smack* smack_cred (int /*<<< orphan*/ ) ; 
 int smk_tskacc (struct task_smack*,struct smack_known*,int /*<<< orphan*/ ,struct smk_audit_info*) ; 

int smk_curacc(struct smack_known *obj_known,
	       u32 mode, struct smk_audit_info *a)
{
	struct task_smack *tsp = smack_cred(current_cred());

	return smk_tskacc(tsp, obj_known, mode, a);
}