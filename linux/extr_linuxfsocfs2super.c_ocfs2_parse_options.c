#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {size_t to; size_t from; } ;
typedef  TYPE_1__ substring_t ;
struct super_block {int dummy; } ;
struct mount_options {int commit_interval; int mount_opt; int atime_quantum; int localalloc_opt; char* cluster_stack; int resv_level; int dir_resv_level; int /*<<< orphan*/  slot; } ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int HZ ; 
 int JBD2_DEFAULT_MAX_COMMIT_AGE ; 
 int MAX_OPT_ARGS ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  OCFS2_CLASSIC_CLUSTER_STACK ; 
 int OCFS2_DEFAULT_ATIME_QUANTUM ; 
 int OCFS2_DEFAULT_RESV_LEVEL ; 
 int /*<<< orphan*/  OCFS2_INVALID_SLOT ; 
 int OCFS2_MAX_RESV_LEVEL ; 
 int OCFS2_MIN_RESV_LEVEL ; 
 int OCFS2_MOUNT_BARRIER ; 
 int OCFS2_MOUNT_COHERENCY_BUFFERED ; 
 int OCFS2_MOUNT_DATA_WRITEBACK ; 
 int OCFS2_MOUNT_ERRORS_CONT ; 
 int OCFS2_MOUNT_ERRORS_PANIC ; 
 int OCFS2_MOUNT_ERRORS_ROFS ; 
 int OCFS2_MOUNT_GRPQUOTA ; 
 int OCFS2_MOUNT_HB_GLOBAL ; 
 int OCFS2_MOUNT_HB_LOCAL ; 
 int OCFS2_MOUNT_HB_NONE ; 
 int OCFS2_MOUNT_INODE64 ; 
 int OCFS2_MOUNT_JOURNAL_ASYNC_COMMIT ; 
 int OCFS2_MOUNT_LOCALFLOCKS ; 
 int OCFS2_MOUNT_NOINTR ; 
 int OCFS2_MOUNT_NOUSERXATTR ; 
 int OCFS2_MOUNT_NO_POSIX_ACL ; 
 int OCFS2_MOUNT_POSIX_ACL ; 
 int OCFS2_MOUNT_USRQUOTA ; 
 size_t OCFS2_STACK_LABEL_LEN ; 
#define  Opt_acl 156 
#define  Opt_atime_quantum 155 
#define  Opt_barrier 154 
#define  Opt_coherency_buffered 153 
#define  Opt_coherency_full 152 
#define  Opt_commit 151 
#define  Opt_data_ordered 150 
#define  Opt_data_writeback 149 
#define  Opt_dir_resv_level 148 
#define  Opt_err_cont 147 
#define  Opt_err_panic 146 
#define  Opt_err_ro 145 
#define  Opt_grpquota 144 
#define  Opt_hb_global 143 
#define  Opt_hb_local 142 
#define  Opt_hb_none 141 
#define  Opt_inode64 140 
#define  Opt_intr 139 
#define  Opt_journal_async_commit 138 
#define  Opt_localalloc 137 
#define  Opt_localflocks 136 
#define  Opt_noacl 135 
#define  Opt_nointr 134 
#define  Opt_nouser_xattr 133 
#define  Opt_resv_level 132 
#define  Opt_slot 131 
#define  Opt_stack 130 
#define  Opt_user_xattr 129 
#define  Opt_usrquota 128 
 int hweight32 (int) ; 
 int /*<<< orphan*/  match_int (TYPE_1__*,int*) ; 
 int match_token (char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memcmp (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,size_t,size_t) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 size_t strnlen (size_t,size_t) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  tokens ; 
 int /*<<< orphan*/  trace_ocfs2_parse_options (int,char*) ; 

__attribute__((used)) static int ocfs2_parse_options(struct super_block *sb,
			       char *options,
			       struct mount_options *mopt,
			       int is_remount)
{
	int status, user_stack = 0;
	char *p;
	u32 tmp;
	int token, option;
	substring_t args[MAX_OPT_ARGS];

	trace_ocfs2_parse_options(is_remount, options ? options : "(none)");

	mopt->commit_interval = 0;
	mopt->mount_opt = OCFS2_MOUNT_NOINTR;
	mopt->atime_quantum = OCFS2_DEFAULT_ATIME_QUANTUM;
	mopt->slot = OCFS2_INVALID_SLOT;
	mopt->localalloc_opt = -1;
	mopt->cluster_stack[0] = '\0';
	mopt->resv_level = OCFS2_DEFAULT_RESV_LEVEL;
	mopt->dir_resv_level = -1;

	if (!options) {
		status = 1;
		goto bail;
	}

	while ((p = strsep(&options, ",")) != NULL) {
		if (!*p)
			continue;

		token = match_token(p, tokens, args);
		switch (token) {
		case Opt_hb_local:
			mopt->mount_opt |= OCFS2_MOUNT_HB_LOCAL;
			break;
		case Opt_hb_none:
			mopt->mount_opt |= OCFS2_MOUNT_HB_NONE;
			break;
		case Opt_hb_global:
			mopt->mount_opt |= OCFS2_MOUNT_HB_GLOBAL;
			break;
		case Opt_barrier:
			if (match_int(&args[0], &option)) {
				status = 0;
				goto bail;
			}
			if (option)
				mopt->mount_opt |= OCFS2_MOUNT_BARRIER;
			else
				mopt->mount_opt &= ~OCFS2_MOUNT_BARRIER;
			break;
		case Opt_intr:
			mopt->mount_opt &= ~OCFS2_MOUNT_NOINTR;
			break;
		case Opt_nointr:
			mopt->mount_opt |= OCFS2_MOUNT_NOINTR;
			break;
		case Opt_err_panic:
			mopt->mount_opt &= ~OCFS2_MOUNT_ERRORS_CONT;
			mopt->mount_opt &= ~OCFS2_MOUNT_ERRORS_ROFS;
			mopt->mount_opt |= OCFS2_MOUNT_ERRORS_PANIC;
			break;
		case Opt_err_ro:
			mopt->mount_opt &= ~OCFS2_MOUNT_ERRORS_CONT;
			mopt->mount_opt &= ~OCFS2_MOUNT_ERRORS_PANIC;
			mopt->mount_opt |= OCFS2_MOUNT_ERRORS_ROFS;
			break;
		case Opt_err_cont:
			mopt->mount_opt &= ~OCFS2_MOUNT_ERRORS_ROFS;
			mopt->mount_opt &= ~OCFS2_MOUNT_ERRORS_PANIC;
			mopt->mount_opt |= OCFS2_MOUNT_ERRORS_CONT;
			break;
		case Opt_data_ordered:
			mopt->mount_opt &= ~OCFS2_MOUNT_DATA_WRITEBACK;
			break;
		case Opt_data_writeback:
			mopt->mount_opt |= OCFS2_MOUNT_DATA_WRITEBACK;
			break;
		case Opt_user_xattr:
			mopt->mount_opt &= ~OCFS2_MOUNT_NOUSERXATTR;
			break;
		case Opt_nouser_xattr:
			mopt->mount_opt |= OCFS2_MOUNT_NOUSERXATTR;
			break;
		case Opt_atime_quantum:
			if (match_int(&args[0], &option)) {
				status = 0;
				goto bail;
			}
			if (option >= 0)
				mopt->atime_quantum = option;
			break;
		case Opt_slot:
			if (match_int(&args[0], &option)) {
				status = 0;
				goto bail;
			}
			if (option)
				mopt->slot = (s16)option;
			break;
		case Opt_commit:
			if (match_int(&args[0], &option)) {
				status = 0;
				goto bail;
			}
			if (option < 0)
				return 0;
			if (option == 0)
				option = JBD2_DEFAULT_MAX_COMMIT_AGE;
			mopt->commit_interval = HZ * option;
			break;
		case Opt_localalloc:
			if (match_int(&args[0], &option)) {
				status = 0;
				goto bail;
			}
			if (option >= 0)
				mopt->localalloc_opt = option;
			break;
		case Opt_localflocks:
			/*
			 * Changing this during remount could race
			 * flock() requests, or "unbalance" existing
			 * ones (e.g., a lock is taken in one mode but
			 * dropped in the other). If users care enough
			 * to flip locking modes during remount, we
			 * could add a "local" flag to individual
			 * flock structures for proper tracking of
			 * state.
			 */
			if (!is_remount)
				mopt->mount_opt |= OCFS2_MOUNT_LOCALFLOCKS;
			break;
		case Opt_stack:
			/* Check both that the option we were passed
			 * is of the right length and that it is a proper
			 * string of the right length.
			 */
			if (((args[0].to - args[0].from) !=
			     OCFS2_STACK_LABEL_LEN) ||
			    (strnlen(args[0].from,
				     OCFS2_STACK_LABEL_LEN) !=
			     OCFS2_STACK_LABEL_LEN)) {
				mlog(ML_ERROR,
				     "Invalid cluster_stack option\n");
				status = 0;
				goto bail;
			}
			memcpy(mopt->cluster_stack, args[0].from,
			       OCFS2_STACK_LABEL_LEN);
			mopt->cluster_stack[OCFS2_STACK_LABEL_LEN] = '\0';
			/*
			 * Open code the memcmp here as we don't have
			 * an osb to pass to
			 * ocfs2_userspace_stack().
			 */
			if (memcmp(mopt->cluster_stack,
				   OCFS2_CLASSIC_CLUSTER_STACK,
				   OCFS2_STACK_LABEL_LEN))
				user_stack = 1;
			break;
		case Opt_inode64:
			mopt->mount_opt |= OCFS2_MOUNT_INODE64;
			break;
		case Opt_usrquota:
			mopt->mount_opt |= OCFS2_MOUNT_USRQUOTA;
			break;
		case Opt_grpquota:
			mopt->mount_opt |= OCFS2_MOUNT_GRPQUOTA;
			break;
		case Opt_coherency_buffered:
			mopt->mount_opt |= OCFS2_MOUNT_COHERENCY_BUFFERED;
			break;
		case Opt_coherency_full:
			mopt->mount_opt &= ~OCFS2_MOUNT_COHERENCY_BUFFERED;
			break;
		case Opt_acl:
			mopt->mount_opt |= OCFS2_MOUNT_POSIX_ACL;
			mopt->mount_opt &= ~OCFS2_MOUNT_NO_POSIX_ACL;
			break;
		case Opt_noacl:
			mopt->mount_opt |= OCFS2_MOUNT_NO_POSIX_ACL;
			mopt->mount_opt &= ~OCFS2_MOUNT_POSIX_ACL;
			break;
		case Opt_resv_level:
			if (is_remount)
				break;
			if (match_int(&args[0], &option)) {
				status = 0;
				goto bail;
			}
			if (option >= OCFS2_MIN_RESV_LEVEL &&
			    option < OCFS2_MAX_RESV_LEVEL)
				mopt->resv_level = option;
			break;
		case Opt_dir_resv_level:
			if (is_remount)
				break;
			if (match_int(&args[0], &option)) {
				status = 0;
				goto bail;
			}
			if (option >= OCFS2_MIN_RESV_LEVEL &&
			    option < OCFS2_MAX_RESV_LEVEL)
				mopt->dir_resv_level = option;
			break;
		case Opt_journal_async_commit:
			mopt->mount_opt |= OCFS2_MOUNT_JOURNAL_ASYNC_COMMIT;
			break;
		default:
			mlog(ML_ERROR,
			     "Unrecognized mount option \"%s\" "
			     "or missing value\n", p);
			status = 0;
			goto bail;
		}
	}

	if (user_stack == 0) {
		/* Ensure only one heartbeat mode */
		tmp = mopt->mount_opt & (OCFS2_MOUNT_HB_LOCAL |
					 OCFS2_MOUNT_HB_GLOBAL |
					 OCFS2_MOUNT_HB_NONE);
		if (hweight32(tmp) != 1) {
			mlog(ML_ERROR, "Invalid heartbeat mount options\n");
			status = 0;
			goto bail;
		}
	}

	status = 1;

bail:
	return status;
}