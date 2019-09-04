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
struct task_struct {int dummy; } ;
struct cred {int /*<<< orphan*/  fsgid; int /*<<< orphan*/  sgid; int /*<<< orphan*/  egid; int /*<<< orphan*/  gid; int /*<<< orphan*/  fsuid; int /*<<< orphan*/  suid; int /*<<< orphan*/  euid; int /*<<< orphan*/  uid; } ;
struct audit_names {int dummy; } ;
struct audit_field {int val; int /*<<< orphan*/  op; } ;
struct audit_context {int dummy; } ;

/* Variables and functions */
#define  AUDIT_COMPARE_AUID_TO_EUID 152 
#define  AUDIT_COMPARE_AUID_TO_FSUID 151 
#define  AUDIT_COMPARE_AUID_TO_OBJ_UID 150 
#define  AUDIT_COMPARE_AUID_TO_SUID 149 
#define  AUDIT_COMPARE_EGID_TO_FSGID 148 
#define  AUDIT_COMPARE_EGID_TO_OBJ_GID 147 
#define  AUDIT_COMPARE_EGID_TO_SGID 146 
#define  AUDIT_COMPARE_EUID_TO_FSUID 145 
#define  AUDIT_COMPARE_EUID_TO_OBJ_UID 144 
#define  AUDIT_COMPARE_EUID_TO_SUID 143 
#define  AUDIT_COMPARE_FSGID_TO_OBJ_GID 142 
#define  AUDIT_COMPARE_FSUID_TO_OBJ_UID 141 
#define  AUDIT_COMPARE_GID_TO_EGID 140 
#define  AUDIT_COMPARE_GID_TO_FSGID 139 
#define  AUDIT_COMPARE_GID_TO_OBJ_GID 138 
#define  AUDIT_COMPARE_GID_TO_SGID 137 
#define  AUDIT_COMPARE_SGID_TO_FSGID 136 
#define  AUDIT_COMPARE_SGID_TO_OBJ_GID 135 
#define  AUDIT_COMPARE_SUID_TO_FSUID 134 
#define  AUDIT_COMPARE_SUID_TO_OBJ_UID 133 
#define  AUDIT_COMPARE_UID_TO_AUID 132 
#define  AUDIT_COMPARE_UID_TO_EUID 131 
#define  AUDIT_COMPARE_UID_TO_FSUID 130 
#define  AUDIT_COMPARE_UID_TO_OBJ_UID 129 
#define  AUDIT_COMPARE_UID_TO_SUID 128 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int audit_compare_gid (int /*<<< orphan*/ ,struct audit_names*,struct audit_field*,struct audit_context*) ; 
 int audit_compare_uid (int /*<<< orphan*/ ,struct audit_names*,struct audit_field*,struct audit_context*) ; 
 int /*<<< orphan*/  audit_get_loginuid (struct task_struct*) ; 
 int audit_gid_comparator (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int audit_uid_comparator (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int audit_field_compare(struct task_struct *tsk,
			       const struct cred *cred,
			       struct audit_field *f,
			       struct audit_context *ctx,
			       struct audit_names *name)
{
	switch (f->val) {
	/* process to file object comparisons */
	case AUDIT_COMPARE_UID_TO_OBJ_UID:
		return audit_compare_uid(cred->uid, name, f, ctx);
	case AUDIT_COMPARE_GID_TO_OBJ_GID:
		return audit_compare_gid(cred->gid, name, f, ctx);
	case AUDIT_COMPARE_EUID_TO_OBJ_UID:
		return audit_compare_uid(cred->euid, name, f, ctx);
	case AUDIT_COMPARE_EGID_TO_OBJ_GID:
		return audit_compare_gid(cred->egid, name, f, ctx);
	case AUDIT_COMPARE_AUID_TO_OBJ_UID:
		return audit_compare_uid(audit_get_loginuid(tsk), name, f, ctx);
	case AUDIT_COMPARE_SUID_TO_OBJ_UID:
		return audit_compare_uid(cred->suid, name, f, ctx);
	case AUDIT_COMPARE_SGID_TO_OBJ_GID:
		return audit_compare_gid(cred->sgid, name, f, ctx);
	case AUDIT_COMPARE_FSUID_TO_OBJ_UID:
		return audit_compare_uid(cred->fsuid, name, f, ctx);
	case AUDIT_COMPARE_FSGID_TO_OBJ_GID:
		return audit_compare_gid(cred->fsgid, name, f, ctx);
	/* uid comparisons */
	case AUDIT_COMPARE_UID_TO_AUID:
		return audit_uid_comparator(cred->uid, f->op,
					    audit_get_loginuid(tsk));
	case AUDIT_COMPARE_UID_TO_EUID:
		return audit_uid_comparator(cred->uid, f->op, cred->euid);
	case AUDIT_COMPARE_UID_TO_SUID:
		return audit_uid_comparator(cred->uid, f->op, cred->suid);
	case AUDIT_COMPARE_UID_TO_FSUID:
		return audit_uid_comparator(cred->uid, f->op, cred->fsuid);
	/* auid comparisons */
	case AUDIT_COMPARE_AUID_TO_EUID:
		return audit_uid_comparator(audit_get_loginuid(tsk), f->op,
					    cred->euid);
	case AUDIT_COMPARE_AUID_TO_SUID:
		return audit_uid_comparator(audit_get_loginuid(tsk), f->op,
					    cred->suid);
	case AUDIT_COMPARE_AUID_TO_FSUID:
		return audit_uid_comparator(audit_get_loginuid(tsk), f->op,
					    cred->fsuid);
	/* euid comparisons */
	case AUDIT_COMPARE_EUID_TO_SUID:
		return audit_uid_comparator(cred->euid, f->op, cred->suid);
	case AUDIT_COMPARE_EUID_TO_FSUID:
		return audit_uid_comparator(cred->euid, f->op, cred->fsuid);
	/* suid comparisons */
	case AUDIT_COMPARE_SUID_TO_FSUID:
		return audit_uid_comparator(cred->suid, f->op, cred->fsuid);
	/* gid comparisons */
	case AUDIT_COMPARE_GID_TO_EGID:
		return audit_gid_comparator(cred->gid, f->op, cred->egid);
	case AUDIT_COMPARE_GID_TO_SGID:
		return audit_gid_comparator(cred->gid, f->op, cred->sgid);
	case AUDIT_COMPARE_GID_TO_FSGID:
		return audit_gid_comparator(cred->gid, f->op, cred->fsgid);
	/* egid comparisons */
	case AUDIT_COMPARE_EGID_TO_SGID:
		return audit_gid_comparator(cred->egid, f->op, cred->sgid);
	case AUDIT_COMPARE_EGID_TO_FSGID:
		return audit_gid_comparator(cred->egid, f->op, cred->fsgid);
	/* sgid comparison */
	case AUDIT_COMPARE_SGID_TO_FSGID:
		return audit_gid_comparator(cred->sgid, f->op, cred->fsgid);
	default:
		WARN(1, "Missing AUDIT_COMPARE define.  Report as a bug\n");
		return 0;
	}
	return 0;
}