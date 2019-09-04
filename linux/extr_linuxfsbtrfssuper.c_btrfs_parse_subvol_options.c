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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  substring_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FS_TREE_OBJECTID ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_OPT_ARGS ; 
#define  Opt_subvol 130 
#define  Opt_subvolid 129 
#define  Opt_subvolrootid 128 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 char* match_strdup (int /*<<< orphan*/ *) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int match_u64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  tokens ; 

__attribute__((used)) static int btrfs_parse_subvol_options(const char *options, char **subvol_name,
		u64 *subvol_objectid)
{
	substring_t args[MAX_OPT_ARGS];
	char *opts, *orig, *p;
	int error = 0;
	u64 subvolid;

	if (!options)
		return 0;

	/*
	 * strsep changes the string, duplicate it because
	 * btrfs_parse_device_options gets called later
	 */
	opts = kstrdup(options, GFP_KERNEL);
	if (!opts)
		return -ENOMEM;
	orig = opts;

	while ((p = strsep(&opts, ",")) != NULL) {
		int token;
		if (!*p)
			continue;

		token = match_token(p, tokens, args);
		switch (token) {
		case Opt_subvol:
			kfree(*subvol_name);
			*subvol_name = match_strdup(&args[0]);
			if (!*subvol_name) {
				error = -ENOMEM;
				goto out;
			}
			break;
		case Opt_subvolid:
			error = match_u64(&args[0], &subvolid);
			if (error)
				goto out;

			/* we want the original fs_tree */
			if (subvolid == 0)
				subvolid = BTRFS_FS_TREE_OBJECTID;

			*subvol_objectid = subvolid;
			break;
		case Opt_subvolrootid:
			pr_warn("BTRFS: 'subvolrootid' mount option is deprecated and has no effect\n");
			break;
		default:
			break;
		}
	}

out:
	kfree(orig);
	return error;
}