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
 int /*<<< orphan*/  CONTEXT_MNT ; 
 int /*<<< orphan*/  DEFCONTEXT_MNT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FSCONTEXT_MNT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_OPT_ARGS ; 
 int /*<<< orphan*/  NUM_SEL_MNT_OPTS ; 
#define  Opt_context 132 
#define  Opt_defcontext 131 
#define  Opt_fscontext 130 
#define  Opt_labelsupport 129 
#define  Opt_rootcontext 128 
 int /*<<< orphan*/  ROOTCONTEXT_MNT ; 
 char* SEL_MOUNT_FAIL_MSG ; 
 void* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* match_strdup (int /*<<< orphan*/ *) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  security_free_mnt_opts (struct security_mnt_opts*) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  tokens ; 

__attribute__((used)) static int selinux_parse_opts_str(char *options,
				  struct security_mnt_opts *opts)
{
	char *p;
	char *context = NULL, *defcontext = NULL;
	char *fscontext = NULL, *rootcontext = NULL;
	int rc, num_mnt_opts = 0;

	opts->num_mnt_opts = 0;

	/* Standard string-based options. */
	while ((p = strsep(&options, "|")) != NULL) {
		int token;
		substring_t args[MAX_OPT_ARGS];

		if (!*p)
			continue;

		token = match_token(p, tokens, args);

		switch (token) {
		case Opt_context:
			if (context || defcontext) {
				rc = -EINVAL;
				pr_warn(SEL_MOUNT_FAIL_MSG);
				goto out_err;
			}
			context = match_strdup(&args[0]);
			if (!context) {
				rc = -ENOMEM;
				goto out_err;
			}
			break;

		case Opt_fscontext:
			if (fscontext) {
				rc = -EINVAL;
				pr_warn(SEL_MOUNT_FAIL_MSG);
				goto out_err;
			}
			fscontext = match_strdup(&args[0]);
			if (!fscontext) {
				rc = -ENOMEM;
				goto out_err;
			}
			break;

		case Opt_rootcontext:
			if (rootcontext) {
				rc = -EINVAL;
				pr_warn(SEL_MOUNT_FAIL_MSG);
				goto out_err;
			}
			rootcontext = match_strdup(&args[0]);
			if (!rootcontext) {
				rc = -ENOMEM;
				goto out_err;
			}
			break;

		case Opt_defcontext:
			if (context || defcontext) {
				rc = -EINVAL;
				pr_warn(SEL_MOUNT_FAIL_MSG);
				goto out_err;
			}
			defcontext = match_strdup(&args[0]);
			if (!defcontext) {
				rc = -ENOMEM;
				goto out_err;
			}
			break;
		case Opt_labelsupport:
			break;
		default:
			rc = -EINVAL;
			pr_warn("SELinux:  unknown mount option\n");
			goto out_err;

		}
	}

	rc = -ENOMEM;
	opts->mnt_opts = kcalloc(NUM_SEL_MNT_OPTS, sizeof(char *), GFP_KERNEL);
	if (!opts->mnt_opts)
		goto out_err;

	opts->mnt_opts_flags = kcalloc(NUM_SEL_MNT_OPTS, sizeof(int),
				       GFP_KERNEL);
	if (!opts->mnt_opts_flags)
		goto out_err;

	if (fscontext) {
		opts->mnt_opts[num_mnt_opts] = fscontext;
		opts->mnt_opts_flags[num_mnt_opts++] = FSCONTEXT_MNT;
	}
	if (context) {
		opts->mnt_opts[num_mnt_opts] = context;
		opts->mnt_opts_flags[num_mnt_opts++] = CONTEXT_MNT;
	}
	if (rootcontext) {
		opts->mnt_opts[num_mnt_opts] = rootcontext;
		opts->mnt_opts_flags[num_mnt_opts++] = ROOTCONTEXT_MNT;
	}
	if (defcontext) {
		opts->mnt_opts[num_mnt_opts] = defcontext;
		opts->mnt_opts_flags[num_mnt_opts++] = DEFCONTEXT_MNT;
	}

	opts->num_mnt_opts = num_mnt_opts;
	return 0;

out_err:
	security_free_mnt_opts(opts);
	kfree(context);
	kfree(defcontext);
	kfree(fscontext);
	kfree(rootcontext);
	return rc;
}