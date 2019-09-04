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
typedef  void* umode_t ;
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  substring_t ;
struct hfs_sb_info {int s_file_umask; int s_dir_umask; int s_quiet; int part; int session; void* nls_io; void* nls_disk; int /*<<< orphan*/  s_creator; int /*<<< orphan*/  s_type; int /*<<< orphan*/  s_gid; int /*<<< orphan*/  s_uid; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int MAX_OPT_ARGS ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  current_gid () ; 
 int /*<<< orphan*/  current_uid () ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int /*<<< orphan*/  gid_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 void* load_nls (char*) ; 
 void* load_nls_default () ; 
 int /*<<< orphan*/  make_kgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  match_fourchar (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  match_int (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  match_octal (int /*<<< orphan*/ *,int*) ; 
 char* match_strdup (int /*<<< orphan*/ *) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  opt_codepage 139 
#define  opt_creator 138 
#define  opt_dir_umask 137 
#define  opt_file_umask 136 
#define  opt_gid 135 
#define  opt_iocharset 134 
#define  opt_part 133 
#define  opt_quiet 132 
#define  opt_session 131 
#define  opt_type 130 
#define  opt_uid 129 
#define  opt_umask 128 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  tokens ; 
 int /*<<< orphan*/  uid_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_options(char *options, struct hfs_sb_info *hsb)
{
	char *p;
	substring_t args[MAX_OPT_ARGS];
	int tmp, token;

	/* initialize the sb with defaults */
	hsb->s_uid = current_uid();
	hsb->s_gid = current_gid();
	hsb->s_file_umask = 0133;
	hsb->s_dir_umask = 0022;
	hsb->s_type = hsb->s_creator = cpu_to_be32(0x3f3f3f3f);	/* == '????' */
	hsb->s_quiet = 0;
	hsb->part = -1;
	hsb->session = -1;

	if (!options)
		return 1;

	while ((p = strsep(&options, ",")) != NULL) {
		if (!*p)
			continue;

		token = match_token(p, tokens, args);
		switch (token) {
		case opt_uid:
			if (match_int(&args[0], &tmp)) {
				pr_err("uid requires an argument\n");
				return 0;
			}
			hsb->s_uid = make_kuid(current_user_ns(), (uid_t)tmp);
			if (!uid_valid(hsb->s_uid)) {
				pr_err("invalid uid %d\n", tmp);
				return 0;
			}
			break;
		case opt_gid:
			if (match_int(&args[0], &tmp)) {
				pr_err("gid requires an argument\n");
				return 0;
			}
			hsb->s_gid = make_kgid(current_user_ns(), (gid_t)tmp);
			if (!gid_valid(hsb->s_gid)) {
				pr_err("invalid gid %d\n", tmp);
				return 0;
			}
			break;
		case opt_umask:
			if (match_octal(&args[0], &tmp)) {
				pr_err("umask requires a value\n");
				return 0;
			}
			hsb->s_file_umask = (umode_t)tmp;
			hsb->s_dir_umask = (umode_t)tmp;
			break;
		case opt_file_umask:
			if (match_octal(&args[0], &tmp)) {
				pr_err("file_umask requires a value\n");
				return 0;
			}
			hsb->s_file_umask = (umode_t)tmp;
			break;
		case opt_dir_umask:
			if (match_octal(&args[0], &tmp)) {
				pr_err("dir_umask requires a value\n");
				return 0;
			}
			hsb->s_dir_umask = (umode_t)tmp;
			break;
		case opt_part:
			if (match_int(&args[0], &hsb->part)) {
				pr_err("part requires an argument\n");
				return 0;
			}
			break;
		case opt_session:
			if (match_int(&args[0], &hsb->session)) {
				pr_err("session requires an argument\n");
				return 0;
			}
			break;
		case opt_type:
			if (match_fourchar(&args[0], &hsb->s_type)) {
				pr_err("type requires a 4 character value\n");
				return 0;
			}
			break;
		case opt_creator:
			if (match_fourchar(&args[0], &hsb->s_creator)) {
				pr_err("creator requires a 4 character value\n");
				return 0;
			}
			break;
		case opt_quiet:
			hsb->s_quiet = 1;
			break;
		case opt_codepage:
			if (hsb->nls_disk) {
				pr_err("unable to change codepage\n");
				return 0;
			}
			p = match_strdup(&args[0]);
			if (p)
				hsb->nls_disk = load_nls(p);
			if (!hsb->nls_disk) {
				pr_err("unable to load codepage \"%s\"\n", p);
				kfree(p);
				return 0;
			}
			kfree(p);
			break;
		case opt_iocharset:
			if (hsb->nls_io) {
				pr_err("unable to change iocharset\n");
				return 0;
			}
			p = match_strdup(&args[0]);
			if (p)
				hsb->nls_io = load_nls(p);
			if (!hsb->nls_io) {
				pr_err("unable to load iocharset \"%s\"\n", p);
				kfree(p);
				return 0;
			}
			kfree(p);
			break;
		default:
			return 0;
		}
	}

	if (hsb->nls_disk && !hsb->nls_io) {
		hsb->nls_io = load_nls_default();
		if (!hsb->nls_io) {
			pr_err("unable to load default iocharset\n");
			return 0;
		}
	}
	hsb->s_dir_umask &= 0777;
	hsb->s_file_umask &= 0577;

	return 1;
}