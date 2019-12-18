#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  substring_t ;
struct pts_mount_opts {int setuid; int setgid; int mode; int ptmxmode; int max; int reserve; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;
struct TYPE_8__ {TYPE_1__* nsproxy; } ;
struct TYPE_7__ {TYPE_2__* nsproxy; } ;
struct TYPE_6__ {scalar_t__ mnt_ns; } ;
struct TYPE_5__ {scalar_t__ mnt_ns; } ;

/* Variables and functions */
 int DEVPTS_DEFAULT_MODE ; 
 int DEVPTS_DEFAULT_PTMX_MODE ; 
 int EINVAL ; 
 int /*<<< orphan*/  GLOBAL_ROOT_GID ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 int MAX_OPT_ARGS ; 
 int NR_UNIX98_PTY_MAX ; 
#define  Opt_gid 133 
#define  Opt_max 132 
#define  Opt_mode 131 
#define  Opt_newinstance 130 
#define  Opt_ptmxmode 129 
#define  Opt_uid 128 
 int PARSE_MOUNT ; 
 int S_IALLUGO ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int /*<<< orphan*/  gid_valid (int /*<<< orphan*/ ) ; 
 TYPE_3__ init_task ; 
 int /*<<< orphan*/  make_kgid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  make_kuid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  match_int (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  match_octal (int /*<<< orphan*/ *,int*) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  tokens ; 
 int /*<<< orphan*/  uid_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_mount_options(char *data, int op, struct pts_mount_opts *opts)
{
	char *p;
	kuid_t uid;
	kgid_t gid;

	opts->setuid  = 0;
	opts->setgid  = 0;
	opts->uid     = GLOBAL_ROOT_UID;
	opts->gid     = GLOBAL_ROOT_GID;
	opts->mode    = DEVPTS_DEFAULT_MODE;
	opts->ptmxmode = DEVPTS_DEFAULT_PTMX_MODE;
	opts->max     = NR_UNIX98_PTY_MAX;

	/* Only allow instances mounted from the initial mount
	 * namespace to tap the reserve pool of ptys.
	 */
	if (op == PARSE_MOUNT)
		opts->reserve =
			(current->nsproxy->mnt_ns == init_task.nsproxy->mnt_ns);

	while ((p = strsep(&data, ",")) != NULL) {
		substring_t args[MAX_OPT_ARGS];
		int token;
		int option;

		if (!*p)
			continue;

		token = match_token(p, tokens, args);
		switch (token) {
		case Opt_uid:
			if (match_int(&args[0], &option))
				return -EINVAL;
			uid = make_kuid(current_user_ns(), option);
			if (!uid_valid(uid))
				return -EINVAL;
			opts->uid = uid;
			opts->setuid = 1;
			break;
		case Opt_gid:
			if (match_int(&args[0], &option))
				return -EINVAL;
			gid = make_kgid(current_user_ns(), option);
			if (!gid_valid(gid))
				return -EINVAL;
			opts->gid = gid;
			opts->setgid = 1;
			break;
		case Opt_mode:
			if (match_octal(&args[0], &option))
				return -EINVAL;
			opts->mode = option & S_IALLUGO;
			break;
		case Opt_ptmxmode:
			if (match_octal(&args[0], &option))
				return -EINVAL;
			opts->ptmxmode = option & S_IALLUGO;
			break;
		case Opt_newinstance:
			break;
		case Opt_max:
			if (match_int(&args[0], &option) ||
			    option < 0 || option > NR_UNIX98_PTY_MAX)
				return -EINVAL;
			opts->max = option;
			break;
		default:
			pr_err("called with bogus options\n");
			return -EINVAL;
		}
	}

	return 0;
}