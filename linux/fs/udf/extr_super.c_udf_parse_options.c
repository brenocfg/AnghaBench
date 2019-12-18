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
struct TYPE_5__ {int /*<<< orphan*/  from; } ;
typedef  TYPE_1__ substring_t ;
struct udf_options {int novrs; int session; int lastblock; int anchor; unsigned int blocksize; int flags; int umask; int fmode; int dmode; int /*<<< orphan*/  nls_map; int /*<<< orphan*/  uid; int /*<<< orphan*/  gid; } ;

/* Variables and functions */
 int MAX_OPT_ARGS ; 
#define  Opt_adinicb 154 
#define  Opt_anchor 153 
#define  Opt_bs 152 
#define  Opt_dmode 151 
#define  Opt_fileset 150 
#define  Opt_fmode 149 
#define  Opt_gforget 148 
#define  Opt_gid 147 
#define  Opt_gignore 146 
#define  Opt_iocharset 145 
#define  Opt_lastblock 144 
#define  Opt_longad 143 
#define  Opt_noadinicb 142 
#define  Opt_nostrict 141 
#define  Opt_novrs 140 
#define  Opt_partition 139 
#define  Opt_rootdir 138 
#define  Opt_session 137 
#define  Opt_shortad 136 
#define  Opt_uforget 135 
#define  Opt_uid 134 
#define  Opt_uignore 133 
#define  Opt_umask 132 
#define  Opt_undelete 131 
#define  Opt_unhide 130 
#define  Opt_utf8 129 
#define  Opt_volume 128 
 int UDF_FLAG_BLOCKSIZE_SET ; 
 int UDF_FLAG_GID_FORGET ; 
 int UDF_FLAG_GID_SET ; 
 int UDF_FLAG_LASTBLOCK_SET ; 
 int UDF_FLAG_NLS_MAP ; 
 int UDF_FLAG_SESSION_SET ; 
 int UDF_FLAG_STRICT ; 
 int UDF_FLAG_UID_FORGET ; 
 int UDF_FLAG_UID_SET ; 
 int UDF_FLAG_UNDELETE ; 
 int UDF_FLAG_UNHIDE ; 
 int UDF_FLAG_USE_AD_IN_ICB ; 
 int UDF_FLAG_USE_SHORT_AD ; 
 int UDF_FLAG_UTF8 ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int /*<<< orphan*/  gid_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_nls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kgid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  make_kuid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  match_int (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  match_octal (TYPE_1__*,int*) ; 
 int match_token (char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pr_err (char*,char*) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  tokens ; 
 int /*<<< orphan*/  uid_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unload_nls (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int udf_parse_options(char *options, struct udf_options *uopt,
			     bool remount)
{
	char *p;
	int option;

	uopt->novrs = 0;
	uopt->session = 0xFFFFFFFF;
	uopt->lastblock = 0;
	uopt->anchor = 0;

	if (!options)
		return 1;

	while ((p = strsep(&options, ",")) != NULL) {
		substring_t args[MAX_OPT_ARGS];
		int token;
		unsigned n;
		if (!*p)
			continue;

		token = match_token(p, tokens, args);
		switch (token) {
		case Opt_novrs:
			uopt->novrs = 1;
			break;
		case Opt_bs:
			if (match_int(&args[0], &option))
				return 0;
			n = option;
			if (n != 512 && n != 1024 && n != 2048 && n != 4096)
				return 0;
			uopt->blocksize = n;
			uopt->flags |= (1 << UDF_FLAG_BLOCKSIZE_SET);
			break;
		case Opt_unhide:
			uopt->flags |= (1 << UDF_FLAG_UNHIDE);
			break;
		case Opt_undelete:
			uopt->flags |= (1 << UDF_FLAG_UNDELETE);
			break;
		case Opt_noadinicb:
			uopt->flags &= ~(1 << UDF_FLAG_USE_AD_IN_ICB);
			break;
		case Opt_adinicb:
			uopt->flags |= (1 << UDF_FLAG_USE_AD_IN_ICB);
			break;
		case Opt_shortad:
			uopt->flags |= (1 << UDF_FLAG_USE_SHORT_AD);
			break;
		case Opt_longad:
			uopt->flags &= ~(1 << UDF_FLAG_USE_SHORT_AD);
			break;
		case Opt_gid:
			if (match_int(args, &option))
				return 0;
			uopt->gid = make_kgid(current_user_ns(), option);
			if (!gid_valid(uopt->gid))
				return 0;
			uopt->flags |= (1 << UDF_FLAG_GID_SET);
			break;
		case Opt_uid:
			if (match_int(args, &option))
				return 0;
			uopt->uid = make_kuid(current_user_ns(), option);
			if (!uid_valid(uopt->uid))
				return 0;
			uopt->flags |= (1 << UDF_FLAG_UID_SET);
			break;
		case Opt_umask:
			if (match_octal(args, &option))
				return 0;
			uopt->umask = option;
			break;
		case Opt_nostrict:
			uopt->flags &= ~(1 << UDF_FLAG_STRICT);
			break;
		case Opt_session:
			if (match_int(args, &option))
				return 0;
			uopt->session = option;
			if (!remount)
				uopt->flags |= (1 << UDF_FLAG_SESSION_SET);
			break;
		case Opt_lastblock:
			if (match_int(args, &option))
				return 0;
			uopt->lastblock = option;
			if (!remount)
				uopt->flags |= (1 << UDF_FLAG_LASTBLOCK_SET);
			break;
		case Opt_anchor:
			if (match_int(args, &option))
				return 0;
			uopt->anchor = option;
			break;
		case Opt_volume:
		case Opt_partition:
		case Opt_fileset:
		case Opt_rootdir:
			/* Ignored (never implemented properly) */
			break;
		case Opt_utf8:
			uopt->flags |= (1 << UDF_FLAG_UTF8);
			break;
		case Opt_iocharset:
			if (!remount) {
				if (uopt->nls_map)
					unload_nls(uopt->nls_map);
				/*
				 * load_nls() failure is handled later in
				 * udf_fill_super() after all options are
				 * parsed.
				 */
				uopt->nls_map = load_nls(args[0].from);
				uopt->flags |= (1 << UDF_FLAG_NLS_MAP);
			}
			break;
		case Opt_uforget:
			uopt->flags |= (1 << UDF_FLAG_UID_FORGET);
			break;
		case Opt_uignore:
		case Opt_gignore:
			/* These options are superseeded by uid=<number> */
			break;
		case Opt_gforget:
			uopt->flags |= (1 << UDF_FLAG_GID_FORGET);
			break;
		case Opt_fmode:
			if (match_octal(args, &option))
				return 0;
			uopt->fmode = option & 0777;
			break;
		case Opt_dmode:
			if (match_octal(args, &option))
				return 0;
			uopt->dmode = option & 0777;
			break;
		default:
			pr_err("bad mount option \"%s\" or missing value\n", p);
			return 0;
		}
	}
	return 1;
}