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
struct inode {int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct autofs_sb_info {int min_proto; int max_proto; int pipefd; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 int AUTOFS_MAX_PROTO_VERSION ; 
 int AUTOFS_MIN_PROTO_VERSION ; 
 int /*<<< orphan*/  AUTOFS_SBI_IGNORE ; 
 int /*<<< orphan*/  AUTOFS_SBI_STRICTEXPIRE ; 
 int MAX_OPT_ARGS ; 
#define  Opt_direct 138 
#define  Opt_fd 137 
#define  Opt_gid 136 
#define  Opt_ignore 135 
#define  Opt_indirect 134 
#define  Opt_maxproto 133 
#define  Opt_minproto 132 
#define  Opt_offset 131 
#define  Opt_pgrp 130 
#define  Opt_strictexpire 129 
#define  Opt_uid 128 
 int /*<<< orphan*/  current_gid () ; 
 int /*<<< orphan*/  current_uid () ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int /*<<< orphan*/  gid_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kgid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  make_kuid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  match_int (int /*<<< orphan*/ *,int*) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_autofs_type_direct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_autofs_type_indirect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_autofs_type_offset (int /*<<< orphan*/ *) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  tokens ; 
 int /*<<< orphan*/  uid_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_options(char *options,
			 struct inode *root, int *pgrp, bool *pgrp_set,
			 struct autofs_sb_info *sbi)
{
	char *p;
	substring_t args[MAX_OPT_ARGS];
	int option;
	int pipefd = -1;
	kuid_t uid;
	kgid_t gid;

	root->i_uid = current_uid();
	root->i_gid = current_gid();

	sbi->min_proto = AUTOFS_MIN_PROTO_VERSION;
	sbi->max_proto = AUTOFS_MAX_PROTO_VERSION;

	sbi->pipefd = -1;

	if (!options)
		return 1;

	while ((p = strsep(&options, ",")) != NULL) {
		int token;

		if (!*p)
			continue;

		token = match_token(p, tokens, args);
		switch (token) {
		case Opt_fd:
			if (match_int(args, &pipefd))
				return 1;
			sbi->pipefd = pipefd;
			break;
		case Opt_uid:
			if (match_int(args, &option))
				return 1;
			uid = make_kuid(current_user_ns(), option);
			if (!uid_valid(uid))
				return 1;
			root->i_uid = uid;
			break;
		case Opt_gid:
			if (match_int(args, &option))
				return 1;
			gid = make_kgid(current_user_ns(), option);
			if (!gid_valid(gid))
				return 1;
			root->i_gid = gid;
			break;
		case Opt_pgrp:
			if (match_int(args, &option))
				return 1;
			*pgrp = option;
			*pgrp_set = true;
			break;
		case Opt_minproto:
			if (match_int(args, &option))
				return 1;
			sbi->min_proto = option;
			break;
		case Opt_maxproto:
			if (match_int(args, &option))
				return 1;
			sbi->max_proto = option;
			break;
		case Opt_indirect:
			set_autofs_type_indirect(&sbi->type);
			break;
		case Opt_direct:
			set_autofs_type_direct(&sbi->type);
			break;
		case Opt_offset:
			set_autofs_type_offset(&sbi->type);
			break;
		case Opt_strictexpire:
			sbi->flags |= AUTOFS_SBI_STRICTEXPIRE;
			break;
		case Opt_ignore:
			sbi->flags |= AUTOFS_SBI_IGNORE;
			break;
		default:
			return 1;
		}
	}
	return (sbi->pipefd < 0);
}