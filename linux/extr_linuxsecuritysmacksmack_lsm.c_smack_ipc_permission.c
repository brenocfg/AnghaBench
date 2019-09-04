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
struct smk_audit_info {int dummy; } ;
struct smack_known {int dummy; } ;
struct kern_ipc_perm {struct smack_known* security; } ;

/* Variables and functions */
 int smack_flags_to_may (short) ; 
 int smk_bu_current (char*,struct smack_known*,int,int) ; 
 int smk_curacc (struct smack_known*,int,struct smk_audit_info*) ; 

__attribute__((used)) static int smack_ipc_permission(struct kern_ipc_perm *ipp, short flag)
{
	struct smack_known *iskp = ipp->security;
	int may = smack_flags_to_may(flag);
	struct smk_audit_info ad;
	int rc;

#ifdef CONFIG_AUDIT
	smk_ad_init(&ad, __func__, LSM_AUDIT_DATA_IPC);
	ad.a.u.ipc_id = ipp->id;
#endif
	rc = smk_curacc(iskp, may, &ad);
	rc = smk_bu_current("svipc", iskp, may, rc);
	return rc;
}