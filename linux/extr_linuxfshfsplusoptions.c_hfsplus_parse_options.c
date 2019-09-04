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
typedef  int /*<<< orphan*/  umode_t ;
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  substring_t ;
struct hfsplus_sb_info {int part; int session; void* nls; int /*<<< orphan*/  flags; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  umask; int /*<<< orphan*/  type; int /*<<< orphan*/  creator; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  HFSPLUS_SB_FORCE ; 
 int /*<<< orphan*/  HFSPLUS_SB_NOBARRIER ; 
 int /*<<< orphan*/  HFSPLUS_SB_NODECOMPOSE ; 
 int MAX_OPT_ARGS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
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
#define  opt_barrier 140 
#define  opt_creator 139 
#define  opt_decompose 138 
#define  opt_force 137 
#define  opt_gid 136 
#define  opt_nls 135 
#define  opt_nobarrier 134 
#define  opt_nodecompose 133 
#define  opt_part 132 
#define  opt_session 131 
#define  opt_type 130 
#define  opt_uid 129 
#define  opt_umask 128 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  tokens ; 
 int /*<<< orphan*/  uid_valid (int /*<<< orphan*/ ) ; 

int hfsplus_parse_options(char *input, struct hfsplus_sb_info *sbi)
{
	char *p;
	substring_t args[MAX_OPT_ARGS];
	int tmp, token;

	if (!input)
		goto done;

	while ((p = strsep(&input, ",")) != NULL) {
		if (!*p)
			continue;

		token = match_token(p, tokens, args);
		switch (token) {
		case opt_creator:
			if (match_fourchar(&args[0], &sbi->creator)) {
				pr_err("creator requires a 4 character value\n");
				return 0;
			}
			break;
		case opt_type:
			if (match_fourchar(&args[0], &sbi->type)) {
				pr_err("type requires a 4 character value\n");
				return 0;
			}
			break;
		case opt_umask:
			if (match_octal(&args[0], &tmp)) {
				pr_err("umask requires a value\n");
				return 0;
			}
			sbi->umask = (umode_t)tmp;
			break;
		case opt_uid:
			if (match_int(&args[0], &tmp)) {
				pr_err("uid requires an argument\n");
				return 0;
			}
			sbi->uid = make_kuid(current_user_ns(), (uid_t)tmp);
			if (!uid_valid(sbi->uid)) {
				pr_err("invalid uid specified\n");
				return 0;
			}
			break;
		case opt_gid:
			if (match_int(&args[0], &tmp)) {
				pr_err("gid requires an argument\n");
				return 0;
			}
			sbi->gid = make_kgid(current_user_ns(), (gid_t)tmp);
			if (!gid_valid(sbi->gid)) {
				pr_err("invalid gid specified\n");
				return 0;
			}
			break;
		case opt_part:
			if (match_int(&args[0], &sbi->part)) {
				pr_err("part requires an argument\n");
				return 0;
			}
			break;
		case opt_session:
			if (match_int(&args[0], &sbi->session)) {
				pr_err("session requires an argument\n");
				return 0;
			}
			break;
		case opt_nls:
			if (sbi->nls) {
				pr_err("unable to change nls mapping\n");
				return 0;
			}
			p = match_strdup(&args[0]);
			if (p)
				sbi->nls = load_nls(p);
			if (!sbi->nls) {
				pr_err("unable to load nls mapping \"%s\"\n",
				       p);
				kfree(p);
				return 0;
			}
			kfree(p);
			break;
		case opt_decompose:
			clear_bit(HFSPLUS_SB_NODECOMPOSE, &sbi->flags);
			break;
		case opt_nodecompose:
			set_bit(HFSPLUS_SB_NODECOMPOSE, &sbi->flags);
			break;
		case opt_barrier:
			clear_bit(HFSPLUS_SB_NOBARRIER, &sbi->flags);
			break;
		case opt_nobarrier:
			set_bit(HFSPLUS_SB_NOBARRIER, &sbi->flags);
			break;
		case opt_force:
			set_bit(HFSPLUS_SB_FORCE, &sbi->flags);
			break;
		default:
			return 0;
		}
	}

done:
	if (!sbi->nls) {
		/* try utf8 first, as this is the old default behaviour */
		sbi->nls = load_nls("utf8");
		if (!sbi->nls)
			sbi->nls = load_nls_default();
		if (!sbi->nls)
			return 0;
	}

	return 1;
}