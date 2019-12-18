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
typedef  int s32 ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 int MAX_OPT_ARGS ; 
#define  Opt_bs 140 
#define  Opt_ignore 139 
#define  Opt_mode 138 
#define  Opt_mufs 137 
#define  Opt_notruncate 136 
#define  Opt_prefix 135 
#define  Opt_protect 134 
#define  Opt_reserved 133 
#define  Opt_root 132 
#define  Opt_setgid 131 
#define  Opt_setuid 130 
#define  Opt_verbose 129 
#define  Opt_volume 128 
 int /*<<< orphan*/  SF_IMMUTABLE ; 
 int /*<<< orphan*/  SF_MUFS ; 
 int /*<<< orphan*/  SF_NO_TRUNCATE ; 
 int /*<<< orphan*/  SF_PREFIX ; 
 int /*<<< orphan*/  SF_SETGID ; 
 int /*<<< orphan*/  SF_SETMODE ; 
 int /*<<< orphan*/  SF_SETUID ; 
 int /*<<< orphan*/  SF_VERBOSE ; 
 int /*<<< orphan*/  affs_set_opt (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_gid () ; 
 int /*<<< orphan*/  current_uid () ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int /*<<< orphan*/  gid_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  make_kgid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  make_kuid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  match_int (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  match_octal (int /*<<< orphan*/ *,int*) ; 
 char* match_strdup (int /*<<< orphan*/ *) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  tokens ; 
 int /*<<< orphan*/  uid_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
parse_options(char *options, kuid_t *uid, kgid_t *gid, int *mode, int *reserved, s32 *root,
		int *blocksize, char **prefix, char *volume, unsigned long *mount_opts)
{
	char *p;
	substring_t args[MAX_OPT_ARGS];

	/* Fill in defaults */

	*uid        = current_uid();
	*gid        = current_gid();
	*reserved   = 2;
	*root       = -1;
	*blocksize  = -1;
	volume[0]   = ':';
	volume[1]   = 0;
	*mount_opts = 0;
	if (!options)
		return 1;

	while ((p = strsep(&options, ",")) != NULL) {
		int token, n, option;
		if (!*p)
			continue;

		token = match_token(p, tokens, args);
		switch (token) {
		case Opt_bs:
			if (match_int(&args[0], &n))
				return 0;
			if (n != 512 && n != 1024 && n != 2048
			    && n != 4096) {
				pr_warn("Invalid blocksize (512, 1024, 2048, 4096 allowed)\n");
				return 0;
			}
			*blocksize = n;
			break;
		case Opt_mode:
			if (match_octal(&args[0], &option))
				return 0;
			*mode = option & 0777;
			affs_set_opt(*mount_opts, SF_SETMODE);
			break;
		case Opt_mufs:
			affs_set_opt(*mount_opts, SF_MUFS);
			break;
		case Opt_notruncate:
			affs_set_opt(*mount_opts, SF_NO_TRUNCATE);
			break;
		case Opt_prefix:
			kfree(*prefix);
			*prefix = match_strdup(&args[0]);
			if (!*prefix)
				return 0;
			affs_set_opt(*mount_opts, SF_PREFIX);
			break;
		case Opt_protect:
			affs_set_opt(*mount_opts, SF_IMMUTABLE);
			break;
		case Opt_reserved:
			if (match_int(&args[0], reserved))
				return 0;
			break;
		case Opt_root:
			if (match_int(&args[0], root))
				return 0;
			break;
		case Opt_setgid:
			if (match_int(&args[0], &option))
				return 0;
			*gid = make_kgid(current_user_ns(), option);
			if (!gid_valid(*gid))
				return 0;
			affs_set_opt(*mount_opts, SF_SETGID);
			break;
		case Opt_setuid:
			if (match_int(&args[0], &option))
				return 0;
			*uid = make_kuid(current_user_ns(), option);
			if (!uid_valid(*uid))
				return 0;
			affs_set_opt(*mount_opts, SF_SETUID);
			break;
		case Opt_verbose:
			affs_set_opt(*mount_opts, SF_VERBOSE);
			break;
		case Opt_volume: {
			char *vol = match_strdup(&args[0]);
			if (!vol)
				return 0;
			strlcpy(volume, vol, 32);
			kfree(vol);
			break;
		}
		case Opt_ignore:
		 	/* Silently ignore the quota options */
			break;
		default:
			pr_warn("Unrecognized mount option \"%s\" or missing value\n",
				p);
			return 0;
		}
	}
	return 1;
}