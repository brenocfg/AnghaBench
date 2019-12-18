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
typedef  int /*<<< orphan*/  u32 ;
struct inode {int /*<<< orphan*/  i_uid; TYPE_2__* i_sb; } ;
struct ima_rule_entry {int flags; int func; int mask; scalar_t__ fsmagic; TYPE_3__* lsm; int /*<<< orphan*/  fowner; int /*<<< orphan*/  (* fowner_op ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  uid; int /*<<< orphan*/  (* uid_op ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  fsuuid; int /*<<< orphan*/  fsname; } ;
struct cred {int /*<<< orphan*/  euid; int /*<<< orphan*/  uid; int /*<<< orphan*/  suid; } ;
typedef  enum ima_hooks { ____Placeholder_ima_hooks } ima_hooks ;
struct TYPE_6__ {int /*<<< orphan*/  rule; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {scalar_t__ s_magic; int /*<<< orphan*/  s_uuid; TYPE_1__* s_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  Audit_equal ; 
 int /*<<< orphan*/  CAP_SETUID ; 
 int IMA_EUID ; 
 int IMA_FOWNER ; 
 int IMA_FSMAGIC ; 
 int IMA_FSNAME ; 
 int IMA_FSUUID ; 
 int IMA_FUNC ; 
 int IMA_INMASK ; 
 int IMA_MASK ; 
 int IMA_UID ; 
 int KEXEC_CMDLINE ; 
#define  LSM_OBJ_ROLE 133 
#define  LSM_OBJ_TYPE 132 
#define  LSM_OBJ_USER 131 
#define  LSM_SUBJ_ROLE 130 
#define  LSM_SUBJ_TYPE 129 
#define  LSM_SUBJ_USER 128 
 int MAX_LSM_RULES ; 
 int POST_SETATTR ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ has_capability_noaudit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int security_filter_rule_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  security_inode_getsecid (struct inode*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ima_match_rules(struct ima_rule_entry *rule, struct inode *inode,
			    const struct cred *cred, u32 secid,
			    enum ima_hooks func, int mask)
{
	int i;

	if (func == KEXEC_CMDLINE) {
		if ((rule->flags & IMA_FUNC) && (rule->func == func))
			return true;
		return false;
	}
	if ((rule->flags & IMA_FUNC) &&
	    (rule->func != func && func != POST_SETATTR))
		return false;
	if ((rule->flags & IMA_MASK) &&
	    (rule->mask != mask && func != POST_SETATTR))
		return false;
	if ((rule->flags & IMA_INMASK) &&
	    (!(rule->mask & mask) && func != POST_SETATTR))
		return false;
	if ((rule->flags & IMA_FSMAGIC)
	    && rule->fsmagic != inode->i_sb->s_magic)
		return false;
	if ((rule->flags & IMA_FSNAME)
	    && strcmp(rule->fsname, inode->i_sb->s_type->name))
		return false;
	if ((rule->flags & IMA_FSUUID) &&
	    !uuid_equal(&rule->fsuuid, &inode->i_sb->s_uuid))
		return false;
	if ((rule->flags & IMA_UID) && !rule->uid_op(cred->uid, rule->uid))
		return false;
	if (rule->flags & IMA_EUID) {
		if (has_capability_noaudit(current, CAP_SETUID)) {
			if (!rule->uid_op(cred->euid, rule->uid)
			    && !rule->uid_op(cred->suid, rule->uid)
			    && !rule->uid_op(cred->uid, rule->uid))
				return false;
		} else if (!rule->uid_op(cred->euid, rule->uid))
			return false;
	}

	if ((rule->flags & IMA_FOWNER) &&
	    !rule->fowner_op(inode->i_uid, rule->fowner))
		return false;
	for (i = 0; i < MAX_LSM_RULES; i++) {
		int rc = 0;
		u32 osid;

		if (!rule->lsm[i].rule)
			continue;

		switch (i) {
		case LSM_OBJ_USER:
		case LSM_OBJ_ROLE:
		case LSM_OBJ_TYPE:
			security_inode_getsecid(inode, &osid);
			rc = security_filter_rule_match(osid,
							rule->lsm[i].type,
							Audit_equal,
							rule->lsm[i].rule);
			break;
		case LSM_SUBJ_USER:
		case LSM_SUBJ_ROLE:
		case LSM_SUBJ_TYPE:
			rc = security_filter_rule_match(secid,
							rule->lsm[i].type,
							Audit_equal,
							rule->lsm[i].rule);
		default:
			break;
		}
		if (!rc)
			return false;
	}
	return true;
}