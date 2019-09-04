#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int umode_t ;
struct TYPE_5__ {char* from; } ;
typedef  TYPE_1__ substring_t ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 int MAX_OPT_ARGS ; 
#define  Opt_case_asis 146 
#define  Opt_case_lower 145 
#define  Opt_check_none 144 
#define  Opt_check_normal 143 
#define  Opt_check_strict 142 
#define  Opt_chkdsk_always 141 
#define  Opt_chkdsk_errors 140 
#define  Opt_chkdsk_no 139 
#define  Opt_eas_no 138 
#define  Opt_eas_ro 137 
#define  Opt_eas_rw 136 
#define  Opt_err_cont 135 
#define  Opt_err_panic 134 
#define  Opt_err_ro 133 
#define  Opt_gid 132 
#define  Opt_help 131 
#define  Opt_timeshift 130 
#define  Opt_uid 129 
#define  Opt_umask 128 
 int /*<<< orphan*/  current_user_ns () ; 
 int /*<<< orphan*/  gid_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kgid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  make_kuid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  match_int (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  match_octal (TYPE_1__*,int*) ; 
 int match_token (char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int simple_strtoul (char*,char**,int /*<<< orphan*/ ) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  tokens ; 
 int /*<<< orphan*/  uid_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_opts(char *opts, kuid_t *uid, kgid_t *gid, umode_t *umask,
		      int *lowercase, int *eas, int *chk, int *errs,
		      int *chkdsk, int *timeshift)
{
	char *p;
	int option;

	if (!opts)
		return 1;

	/*pr_info("Parsing opts: '%s'\n",opts);*/

	while ((p = strsep(&opts, ",")) != NULL) {
		substring_t args[MAX_OPT_ARGS];
		int token;
		if (!*p)
			continue;

		token = match_token(p, tokens, args);
		switch (token) {
		case Opt_help:
			return 2;
		case Opt_uid:
			if (match_int(args, &option))
				return 0;
			*uid = make_kuid(current_user_ns(), option);
			if (!uid_valid(*uid))
				return 0;
			break;
		case Opt_gid:
			if (match_int(args, &option))
				return 0;
			*gid = make_kgid(current_user_ns(), option);
			if (!gid_valid(*gid))
				return 0;
			break;
		case Opt_umask:
			if (match_octal(args, &option))
				return 0;
			*umask = option;
			break;
		case Opt_case_lower:
			*lowercase = 1;
			break;
		case Opt_case_asis:
			*lowercase = 0;
			break;
		case Opt_check_none:
			*chk = 0;
			break;
		case Opt_check_normal:
			*chk = 1;
			break;
		case Opt_check_strict:
			*chk = 2;
			break;
		case Opt_err_cont:
			*errs = 0;
			break;
		case Opt_err_ro:
			*errs = 1;
			break;
		case Opt_err_panic:
			*errs = 2;
			break;
		case Opt_eas_no:
			*eas = 0;
			break;
		case Opt_eas_ro:
			*eas = 1;
			break;
		case Opt_eas_rw:
			*eas = 2;
			break;
		case Opt_chkdsk_no:
			*chkdsk = 0;
			break;
		case Opt_chkdsk_errors:
			*chkdsk = 1;
			break;
		case Opt_chkdsk_always:
			*chkdsk = 2;
			break;
		case Opt_timeshift:
		{
			int m = 1;
			char *rhs = args[0].from;
			if (!rhs || !*rhs)
				return 0;
			if (*rhs == '-') m = -1;
			if (*rhs == '+' || *rhs == '-') rhs++;
			*timeshift = simple_strtoul(rhs, &rhs, 0) * m;
			if (*rhs)
				return 0;
			break;
		}
		default:
			return 0;
		}
	}
	return 1;
}