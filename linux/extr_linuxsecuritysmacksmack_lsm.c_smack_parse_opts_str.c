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
struct security_mnt_opts {int num_mnt_opts; char** mnt_opts; int /*<<< orphan*/ * mnt_opts_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FSDEFAULT_MNT ; 
 int /*<<< orphan*/  FSFLOOR_MNT ; 
 int /*<<< orphan*/  FSHAT_MNT ; 
 int /*<<< orphan*/  FSROOT_MNT ; 
 int /*<<< orphan*/  FSTRANS_MNT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_OPT_ARGS ; 
 int /*<<< orphan*/  NUM_SMK_MNT_OPTS ; 
#define  Opt_fsdefault 132 
#define  Opt_fsfloor 131 
#define  Opt_fshat 130 
#define  Opt_fsroot 129 
#define  Opt_fstransmute 128 
 void* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* match_strdup (int /*<<< orphan*/ *) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  smk_mount_tokens ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int smack_parse_opts_str(char *options,
		struct security_mnt_opts *opts)
{
	char *p;
	char *fsdefault = NULL;
	char *fsfloor = NULL;
	char *fshat = NULL;
	char *fsroot = NULL;
	char *fstransmute = NULL;
	int rc = -ENOMEM;
	int num_mnt_opts = 0;
	int token;

	opts->num_mnt_opts = 0;

	if (!options)
		return 0;

	while ((p = strsep(&options, ",")) != NULL) {
		substring_t args[MAX_OPT_ARGS];

		if (!*p)
			continue;

		token = match_token(p, smk_mount_tokens, args);

		switch (token) {
		case Opt_fsdefault:
			if (fsdefault)
				goto out_opt_err;
			fsdefault = match_strdup(&args[0]);
			if (!fsdefault)
				goto out_err;
			break;
		case Opt_fsfloor:
			if (fsfloor)
				goto out_opt_err;
			fsfloor = match_strdup(&args[0]);
			if (!fsfloor)
				goto out_err;
			break;
		case Opt_fshat:
			if (fshat)
				goto out_opt_err;
			fshat = match_strdup(&args[0]);
			if (!fshat)
				goto out_err;
			break;
		case Opt_fsroot:
			if (fsroot)
				goto out_opt_err;
			fsroot = match_strdup(&args[0]);
			if (!fsroot)
				goto out_err;
			break;
		case Opt_fstransmute:
			if (fstransmute)
				goto out_opt_err;
			fstransmute = match_strdup(&args[0]);
			if (!fstransmute)
				goto out_err;
			break;
		default:
			rc = -EINVAL;
			pr_warn("Smack:  unknown mount option\n");
			goto out_err;
		}
	}

	opts->mnt_opts = kcalloc(NUM_SMK_MNT_OPTS, sizeof(char *), GFP_KERNEL);
	if (!opts->mnt_opts)
		goto out_err;

	opts->mnt_opts_flags = kcalloc(NUM_SMK_MNT_OPTS, sizeof(int),
			GFP_KERNEL);
	if (!opts->mnt_opts_flags)
		goto out_err;

	if (fsdefault) {
		opts->mnt_opts[num_mnt_opts] = fsdefault;
		opts->mnt_opts_flags[num_mnt_opts++] = FSDEFAULT_MNT;
	}
	if (fsfloor) {
		opts->mnt_opts[num_mnt_opts] = fsfloor;
		opts->mnt_opts_flags[num_mnt_opts++] = FSFLOOR_MNT;
	}
	if (fshat) {
		opts->mnt_opts[num_mnt_opts] = fshat;
		opts->mnt_opts_flags[num_mnt_opts++] = FSHAT_MNT;
	}
	if (fsroot) {
		opts->mnt_opts[num_mnt_opts] = fsroot;
		opts->mnt_opts_flags[num_mnt_opts++] = FSROOT_MNT;
	}
	if (fstransmute) {
		opts->mnt_opts[num_mnt_opts] = fstransmute;
		opts->mnt_opts_flags[num_mnt_opts++] = FSTRANS_MNT;
	}

	opts->num_mnt_opts = num_mnt_opts;
	return 0;

out_opt_err:
	rc = -EINVAL;
	pr_warn("Smack: duplicate mount options\n");

out_err:
	kfree(fsdefault);
	kfree(fsfloor);
	kfree(fshat);
	kfree(fsroot);
	kfree(fstransmute);
	return rc;
}