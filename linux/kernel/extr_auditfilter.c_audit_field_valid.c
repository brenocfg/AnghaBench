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
struct audit_field {int type; int val; int /*<<< orphan*/  op; } ;
struct TYPE_2__ {int listnr; } ;
struct audit_entry {TYPE_1__ rule; } ;

/* Variables and functions */
 int AF_MAX ; 
#define  AUDIT_ARCH 174 
#define  AUDIT_ARG0 173 
#define  AUDIT_ARG1 172 
#define  AUDIT_ARG2 171 
#define  AUDIT_ARG3 170 
#define  AUDIT_DEVMAJOR 169 
#define  AUDIT_DEVMINOR 168 
#define  AUDIT_DIR 167 
#define  AUDIT_EGID 166 
#define  AUDIT_EUID 165 
#define  AUDIT_EXE 164 
#define  AUDIT_EXIT 163 
#define  AUDIT_FIELD_COMPARE 162 
#define  AUDIT_FILETYPE 161 
#define  AUDIT_FILTERKEY 160 
 int AUDIT_FILTER_EXCLUDE ; 
#define  AUDIT_FILTER_FS 159 
 int AUDIT_FILTER_USER ; 
#define  AUDIT_FSGID 158 
#define  AUDIT_FSTYPE 157 
#define  AUDIT_FSUID 156 
#define  AUDIT_GID 155 
#define  AUDIT_INODE 154 
#define  AUDIT_LOGINUID 153 
#define  AUDIT_LOGINUID_SET 152 
 int AUDIT_MAX_FIELD_COMPARE ; 
#define  AUDIT_MSGTYPE 151 
#define  AUDIT_OBJ_GID 150 
#define  AUDIT_OBJ_LEV_HIGH 149 
#define  AUDIT_OBJ_LEV_LOW 148 
#define  AUDIT_OBJ_ROLE 147 
#define  AUDIT_OBJ_TYPE 146 
#define  AUDIT_OBJ_UID 145 
#define  AUDIT_OBJ_USER 144 
#define  AUDIT_PERM 143 
#define  AUDIT_PERS 142 
#define  AUDIT_PID 141 
#define  AUDIT_PPID 140 
#define  AUDIT_SADDR_FAM 139 
#define  AUDIT_SESSIONID 138 
#define  AUDIT_SGID 137 
#define  AUDIT_SUBJ_CLR 136 
#define  AUDIT_SUBJ_ROLE 135 
#define  AUDIT_SUBJ_SEN 134 
#define  AUDIT_SUBJ_TYPE 133 
#define  AUDIT_SUBJ_USER 132 
#define  AUDIT_SUCCESS 131 
#define  AUDIT_SUID 130 
#define  AUDIT_UID 129 
#define  AUDIT_WATCH 128 
 int /*<<< orphan*/  Audit_bitmask ; 
 int /*<<< orphan*/  Audit_bittest ; 
 int /*<<< orphan*/  Audit_equal ; 
 int /*<<< orphan*/  Audit_not_equal ; 
 int EINVAL ; 
 int S_IFMT ; 

__attribute__((used)) static int audit_field_valid(struct audit_entry *entry, struct audit_field *f)
{
	switch (f->type) {
	case AUDIT_MSGTYPE:
		if (entry->rule.listnr != AUDIT_FILTER_EXCLUDE &&
		    entry->rule.listnr != AUDIT_FILTER_USER)
			return -EINVAL;
		break;
	case AUDIT_FSTYPE:
		if (entry->rule.listnr != AUDIT_FILTER_FS)
			return -EINVAL;
		break;
	}

	switch (entry->rule.listnr) {
	case AUDIT_FILTER_FS:
		switch(f->type) {
		case AUDIT_FSTYPE:
		case AUDIT_FILTERKEY:
			break;
		default:
			return -EINVAL;
		}
	}

	/* Check for valid field type and op */
	switch (f->type) {
	case AUDIT_ARG0:
	case AUDIT_ARG1:
	case AUDIT_ARG2:
	case AUDIT_ARG3:
	case AUDIT_PERS: /* <uapi/linux/personality.h> */
	case AUDIT_DEVMINOR:
		/* all ops are valid */
		break;
	case AUDIT_UID:
	case AUDIT_EUID:
	case AUDIT_SUID:
	case AUDIT_FSUID:
	case AUDIT_LOGINUID:
	case AUDIT_OBJ_UID:
	case AUDIT_GID:
	case AUDIT_EGID:
	case AUDIT_SGID:
	case AUDIT_FSGID:
	case AUDIT_OBJ_GID:
	case AUDIT_PID:
	case AUDIT_MSGTYPE:
	case AUDIT_PPID:
	case AUDIT_DEVMAJOR:
	case AUDIT_EXIT:
	case AUDIT_SUCCESS:
	case AUDIT_INODE:
	case AUDIT_SESSIONID:
	case AUDIT_SUBJ_SEN:
	case AUDIT_SUBJ_CLR:
	case AUDIT_OBJ_LEV_LOW:
	case AUDIT_OBJ_LEV_HIGH:
	case AUDIT_SADDR_FAM:
		/* bit ops are only useful on syscall args */
		if (f->op == Audit_bitmask || f->op == Audit_bittest)
			return -EINVAL;
		break;
	case AUDIT_SUBJ_USER:
	case AUDIT_SUBJ_ROLE:
	case AUDIT_SUBJ_TYPE:
	case AUDIT_OBJ_USER:
	case AUDIT_OBJ_ROLE:
	case AUDIT_OBJ_TYPE:
	case AUDIT_WATCH:
	case AUDIT_DIR:
	case AUDIT_FILTERKEY:
	case AUDIT_LOGINUID_SET:
	case AUDIT_ARCH:
	case AUDIT_FSTYPE:
	case AUDIT_PERM:
	case AUDIT_FILETYPE:
	case AUDIT_FIELD_COMPARE:
	case AUDIT_EXE:
		/* only equal and not equal valid ops */
		if (f->op != Audit_not_equal && f->op != Audit_equal)
			return -EINVAL;
		break;
	default:
		/* field not recognized */
		return -EINVAL;
	}

	/* Check for select valid field values */
	switch (f->type) {
	case AUDIT_LOGINUID_SET:
		if ((f->val != 0) && (f->val != 1))
			return -EINVAL;
		break;
	case AUDIT_PERM:
		if (f->val & ~15)
			return -EINVAL;
		break;
	case AUDIT_FILETYPE:
		if (f->val & ~S_IFMT)
			return -EINVAL;
		break;
	case AUDIT_FIELD_COMPARE:
		if (f->val > AUDIT_MAX_FIELD_COMPARE)
			return -EINVAL;
		break;
	case AUDIT_SADDR_FAM:
		if (f->val >= AF_MAX)
			return -EINVAL;
		break;
	default:
		break;
	}

	return 0;
}