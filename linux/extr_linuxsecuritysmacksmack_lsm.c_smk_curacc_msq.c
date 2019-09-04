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
struct kern_ipc_perm {int dummy; } ;

/* Variables and functions */
 struct smack_known* smack_of_ipc (struct kern_ipc_perm*) ; 
 int smk_bu_current (char*,struct smack_known*,int,int) ; 
 int smk_curacc (struct smack_known*,int,struct smk_audit_info*) ; 

__attribute__((used)) static int smk_curacc_msq(struct kern_ipc_perm *isp, int access)
{
	struct smack_known *msp = smack_of_ipc(isp);
	struct smk_audit_info ad;
	int rc;

#ifdef CONFIG_AUDIT
	smk_ad_init(&ad, __func__, LSM_AUDIT_DATA_IPC);
	ad.a.u.ipc_id = isp->id;
#endif
	rc = smk_curacc(msp, access, &ad);
	rc = smk_bu_current("msq", msp, access, rc);
	return rc;
}