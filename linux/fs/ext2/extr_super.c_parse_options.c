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
typedef  int /*<<< orphan*/  substring_t ;
struct super_block {int dummy; } ;
struct ext2_mount_options {int /*<<< orphan*/  s_mount_opt; int /*<<< orphan*/  s_resgid; int /*<<< orphan*/  s_resuid; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK ; 
 int /*<<< orphan*/  DAX ; 
 int /*<<< orphan*/  DEBUG ; 
 int /*<<< orphan*/  ERRORS_CONT ; 
 int /*<<< orphan*/  ERRORS_PANIC ; 
 int /*<<< orphan*/  ERRORS_RO ; 
 int /*<<< orphan*/  GRPID ; 
 int /*<<< orphan*/  GRPQUOTA ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int MAX_OPT_ARGS ; 
 int /*<<< orphan*/  MINIX_DF ; 
 int /*<<< orphan*/  NOBH ; 
 int /*<<< orphan*/  NO_UID32 ; 
 int /*<<< orphan*/  OLDALLOC ; 
#define  Opt_acl 155 
#define  Opt_bsd_df 154 
#define  Opt_dax 153 
#define  Opt_debug 152 
#define  Opt_err_cont 151 
#define  Opt_err_panic 150 
#define  Opt_err_ro 149 
#define  Opt_grpid 148 
#define  Opt_grpquota 147 
#define  Opt_ignore 146 
#define  Opt_minix_df 145 
#define  Opt_noacl 144 
#define  Opt_nobh 143 
#define  Opt_nocheck 142 
#define  Opt_nogrpid 141 
#define  Opt_noreservation 140 
#define  Opt_nouid32 139 
#define  Opt_nouser_xattr 138 
#define  Opt_oldalloc 137 
#define  Opt_orlov 136 
#define  Opt_quota 135 
#define  Opt_reservation 134 
#define  Opt_resgid 133 
#define  Opt_resuid 132 
#define  Opt_sb 131 
#define  Opt_user_xattr 130 
#define  Opt_usrquota 129 
#define  Opt_xip 128 
 int /*<<< orphan*/  POSIX_ACL ; 
 int /*<<< orphan*/  RESERVATION ; 
 int /*<<< orphan*/  USRQUOTA ; 
 int /*<<< orphan*/  XATTR_USER ; 
 int /*<<< orphan*/  XIP ; 
 int /*<<< orphan*/  clear_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int /*<<< orphan*/  ext2_msg (struct super_block*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gid_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kgid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  make_kuid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  match_int (int /*<<< orphan*/ *,int*) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  tokens ; 
 int /*<<< orphan*/  uid_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_options(char *options, struct super_block *sb,
			 struct ext2_mount_options *opts)
{
	char *p;
	substring_t args[MAX_OPT_ARGS];
	int option;
	kuid_t uid;
	kgid_t gid;

	if (!options)
		return 1;

	while ((p = strsep (&options, ",")) != NULL) {
		int token;
		if (!*p)
			continue;

		token = match_token(p, tokens, args);
		switch (token) {
		case Opt_bsd_df:
			clear_opt (opts->s_mount_opt, MINIX_DF);
			break;
		case Opt_minix_df:
			set_opt (opts->s_mount_opt, MINIX_DF);
			break;
		case Opt_grpid:
			set_opt (opts->s_mount_opt, GRPID);
			break;
		case Opt_nogrpid:
			clear_opt (opts->s_mount_opt, GRPID);
			break;
		case Opt_resuid:
			if (match_int(&args[0], &option))
				return 0;
			uid = make_kuid(current_user_ns(), option);
			if (!uid_valid(uid)) {
				ext2_msg(sb, KERN_ERR, "Invalid uid value %d", option);
				return 0;

			}
			opts->s_resuid = uid;
			break;
		case Opt_resgid:
			if (match_int(&args[0], &option))
				return 0;
			gid = make_kgid(current_user_ns(), option);
			if (!gid_valid(gid)) {
				ext2_msg(sb, KERN_ERR, "Invalid gid value %d", option);
				return 0;
			}
			opts->s_resgid = gid;
			break;
		case Opt_sb:
			/* handled by get_sb_block() instead of here */
			/* *sb_block = match_int(&args[0]); */
			break;
		case Opt_err_panic:
			clear_opt (opts->s_mount_opt, ERRORS_CONT);
			clear_opt (opts->s_mount_opt, ERRORS_RO);
			set_opt (opts->s_mount_opt, ERRORS_PANIC);
			break;
		case Opt_err_ro:
			clear_opt (opts->s_mount_opt, ERRORS_CONT);
			clear_opt (opts->s_mount_opt, ERRORS_PANIC);
			set_opt (opts->s_mount_opt, ERRORS_RO);
			break;
		case Opt_err_cont:
			clear_opt (opts->s_mount_opt, ERRORS_RO);
			clear_opt (opts->s_mount_opt, ERRORS_PANIC);
			set_opt (opts->s_mount_opt, ERRORS_CONT);
			break;
		case Opt_nouid32:
			set_opt (opts->s_mount_opt, NO_UID32);
			break;
		case Opt_nocheck:
			ext2_msg(sb, KERN_WARNING,
				"Option nocheck/check=none is deprecated and"
				" will be removed in June 2020.");
			clear_opt (opts->s_mount_opt, CHECK);
			break;
		case Opt_debug:
			set_opt (opts->s_mount_opt, DEBUG);
			break;
		case Opt_oldalloc:
			set_opt (opts->s_mount_opt, OLDALLOC);
			break;
		case Opt_orlov:
			clear_opt (opts->s_mount_opt, OLDALLOC);
			break;
		case Opt_nobh:
			set_opt (opts->s_mount_opt, NOBH);
			break;
#ifdef CONFIG_EXT2_FS_XATTR
		case Opt_user_xattr:
			set_opt (opts->s_mount_opt, XATTR_USER);
			break;
		case Opt_nouser_xattr:
			clear_opt (opts->s_mount_opt, XATTR_USER);
			break;
#else
		case Opt_user_xattr:
		case Opt_nouser_xattr:
			ext2_msg(sb, KERN_INFO, "(no)user_xattr options"
				"not supported");
			break;
#endif
#ifdef CONFIG_EXT2_FS_POSIX_ACL
		case Opt_acl:
			set_opt(opts->s_mount_opt, POSIX_ACL);
			break;
		case Opt_noacl:
			clear_opt(opts->s_mount_opt, POSIX_ACL);
			break;
#else
		case Opt_acl:
		case Opt_noacl:
			ext2_msg(sb, KERN_INFO,
				"(no)acl options not supported");
			break;
#endif
		case Opt_xip:
			ext2_msg(sb, KERN_INFO, "use dax instead of xip");
			set_opt(opts->s_mount_opt, XIP);
			/* Fall through */
		case Opt_dax:
#ifdef CONFIG_FS_DAX
			ext2_msg(sb, KERN_WARNING,
		"DAX enabled. Warning: EXPERIMENTAL, use at your own risk");
			set_opt(opts->s_mount_opt, DAX);
#else
			ext2_msg(sb, KERN_INFO, "dax option not supported");
#endif
			break;

#if defined(CONFIG_QUOTA)
		case Opt_quota:
		case Opt_usrquota:
			set_opt(opts->s_mount_opt, USRQUOTA);
			break;

		case Opt_grpquota:
			set_opt(opts->s_mount_opt, GRPQUOTA);
			break;
#else
		case Opt_quota:
		case Opt_usrquota:
		case Opt_grpquota:
			ext2_msg(sb, KERN_INFO,
				"quota operations not supported");
			break;
#endif

		case Opt_reservation:
			set_opt(opts->s_mount_opt, RESERVATION);
			ext2_msg(sb, KERN_INFO, "reservations ON");
			break;
		case Opt_noreservation:
			clear_opt(opts->s_mount_opt, RESERVATION);
			ext2_msg(sb, KERN_INFO, "reservations OFF");
			break;
		case Opt_ignore:
			break;
		default:
			return 0;
		}
	}
	return 1;
}