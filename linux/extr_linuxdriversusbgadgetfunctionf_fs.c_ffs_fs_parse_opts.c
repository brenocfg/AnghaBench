#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long mode; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct ffs_sb_fill_data {int no_disconnect; unsigned long root_mode; TYPE_1__ perms; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ENTER () ; 
 unsigned long S_IFDIR ; 
 unsigned long S_IFREG ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int /*<<< orphan*/  gid_valid (int /*<<< orphan*/ ) ; 
 scalar_t__ kstrtoul (char*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  make_kgid (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  make_kuid (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  pr_err (char*,char*,...) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  uid_valid (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ffs_fs_parse_opts(struct ffs_sb_fill_data *data, char *opts)
{
	ENTER();

	if (!opts || !*opts)
		return 0;

	for (;;) {
		unsigned long value;
		char *eq, *comma;

		/* Option limit */
		comma = strchr(opts, ',');
		if (comma)
			*comma = 0;

		/* Value limit */
		eq = strchr(opts, '=');
		if (unlikely(!eq)) {
			pr_err("'=' missing in %s\n", opts);
			return -EINVAL;
		}
		*eq = 0;

		/* Parse value */
		if (kstrtoul(eq + 1, 0, &value)) {
			pr_err("%s: invalid value: %s\n", opts, eq + 1);
			return -EINVAL;
		}

		/* Interpret option */
		switch (eq - opts) {
		case 13:
			if (!memcmp(opts, "no_disconnect", 13))
				data->no_disconnect = !!value;
			else
				goto invalid;
			break;
		case 5:
			if (!memcmp(opts, "rmode", 5))
				data->root_mode  = (value & 0555) | S_IFDIR;
			else if (!memcmp(opts, "fmode", 5))
				data->perms.mode = (value & 0666) | S_IFREG;
			else
				goto invalid;
			break;

		case 4:
			if (!memcmp(opts, "mode", 4)) {
				data->root_mode  = (value & 0555) | S_IFDIR;
				data->perms.mode = (value & 0666) | S_IFREG;
			} else {
				goto invalid;
			}
			break;

		case 3:
			if (!memcmp(opts, "uid", 3)) {
				data->perms.uid = make_kuid(current_user_ns(), value);
				if (!uid_valid(data->perms.uid)) {
					pr_err("%s: unmapped value: %lu\n", opts, value);
					return -EINVAL;
				}
			} else if (!memcmp(opts, "gid", 3)) {
				data->perms.gid = make_kgid(current_user_ns(), value);
				if (!gid_valid(data->perms.gid)) {
					pr_err("%s: unmapped value: %lu\n", opts, value);
					return -EINVAL;
				}
			} else {
				goto invalid;
			}
			break;

		default:
invalid:
			pr_err("%s: invalid option\n", opts);
			return -EINVAL;
		}

		/* Next iteration */
		if (!comma)
			break;
		opts = comma + 1;
	}

	return 0;
}