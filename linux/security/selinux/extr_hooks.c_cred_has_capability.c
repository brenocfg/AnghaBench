#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct cred {int dummy; } ;
struct TYPE_2__ {int cap; } ;
struct common_audit_data {TYPE_1__ u; int /*<<< orphan*/  type; } ;
struct av_decision {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 unsigned int CAP_OPT_NOAUDIT ; 
 int CAP_TO_INDEX (int) ; 
 int /*<<< orphan*/  CAP_TO_MASK (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  LSM_AUDIT_DATA_CAP ; 
 int /*<<< orphan*/  SECCLASS_CAP2_USERNS ; 
 int /*<<< orphan*/  SECCLASS_CAPABILITY ; 
 int /*<<< orphan*/  SECCLASS_CAPABILITY2 ; 
 int /*<<< orphan*/  SECCLASS_CAP_USERNS ; 
 int avc_audit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct av_decision*,int,struct common_audit_data*,int /*<<< orphan*/ ) ; 
 int avc_has_perm_noaudit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct av_decision*) ; 
 int /*<<< orphan*/  cred_sid (struct cred const*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  selinux_state ; 

__attribute__((used)) static int cred_has_capability(const struct cred *cred,
			       int cap, unsigned int opts, bool initns)
{
	struct common_audit_data ad;
	struct av_decision avd;
	u16 sclass;
	u32 sid = cred_sid(cred);
	u32 av = CAP_TO_MASK(cap);
	int rc;

	ad.type = LSM_AUDIT_DATA_CAP;
	ad.u.cap = cap;

	switch (CAP_TO_INDEX(cap)) {
	case 0:
		sclass = initns ? SECCLASS_CAPABILITY : SECCLASS_CAP_USERNS;
		break;
	case 1:
		sclass = initns ? SECCLASS_CAPABILITY2 : SECCLASS_CAP2_USERNS;
		break;
	default:
		pr_err("SELinux:  out of range capability %d\n", cap);
		BUG();
		return -EINVAL;
	}

	rc = avc_has_perm_noaudit(&selinux_state,
				  sid, sid, sclass, av, 0, &avd);
	if (!(opts & CAP_OPT_NOAUDIT)) {
		int rc2 = avc_audit(&selinux_state,
				    sid, sid, sclass, av, &avd, rc, &ad, 0);
		if (rc2)
			return rc2;
	}
	return rc;
}