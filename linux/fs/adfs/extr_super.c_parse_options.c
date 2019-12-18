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
struct adfs_sb_info {int s_owner_mask; int s_other_mask; int s_ftsuffix; int /*<<< orphan*/  s_gid; int /*<<< orphan*/  s_uid; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int MAX_OPT_ARGS ; 
#define  Opt_ftsuffix 132 
#define  Opt_gid 131 
#define  Opt_othmask 130 
#define  Opt_ownmask 129 
#define  Opt_uid 128 
 int /*<<< orphan*/  adfs_msg (struct super_block*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int /*<<< orphan*/  gid_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kgid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  make_kuid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  match_int (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  match_octal (int /*<<< orphan*/ *,int*) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  tokens ; 
 int /*<<< orphan*/  uid_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_options(struct super_block *sb, struct adfs_sb_info *asb,
			 char *options)
{
	char *p;
	int option;

	if (!options)
		return 0;

	while ((p = strsep(&options, ",")) != NULL) {
		substring_t args[MAX_OPT_ARGS];
		int token;
		if (!*p)
			continue;

		token = match_token(p, tokens, args);
		switch (token) {
		case Opt_uid:
			if (match_int(args, &option))
				return -EINVAL;
			asb->s_uid = make_kuid(current_user_ns(), option);
			if (!uid_valid(asb->s_uid))
				return -EINVAL;
			break;
		case Opt_gid:
			if (match_int(args, &option))
				return -EINVAL;
			asb->s_gid = make_kgid(current_user_ns(), option);
			if (!gid_valid(asb->s_gid))
				return -EINVAL;
			break;
		case Opt_ownmask:
			if (match_octal(args, &option))
				return -EINVAL;
			asb->s_owner_mask = option;
			break;
		case Opt_othmask:
			if (match_octal(args, &option))
				return -EINVAL;
			asb->s_other_mask = option;
			break;
		case Opt_ftsuffix:
			if (match_int(args, &option))
				return -EINVAL;
			asb->s_ftsuffix = option;
			break;
		default:
			adfs_msg(sb, KERN_ERR,
				 "unrecognised mount option \"%s\" or missing value",
				 p);
			return -EINVAL;
		}
	}
	return 0;
}