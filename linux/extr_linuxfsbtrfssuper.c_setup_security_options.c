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
struct super_block {int dummy; } ;
struct security_mnt_opts {int dummy; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 int security_sb_set_mnt_opts (struct super_block*,struct security_mnt_opts*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int setup_security_options(struct btrfs_fs_info *fs_info,
				  struct super_block *sb,
				  struct security_mnt_opts *sec_opts)
{
	int ret = 0;

	/*
	 * Call security_sb_set_mnt_opts() to check whether new sec_opts
	 * is valid.
	 */
	ret = security_sb_set_mnt_opts(sb, sec_opts, 0, NULL);
	if (ret)
		return ret;

#ifdef CONFIG_SECURITY
	if (!fs_info->security_opts.num_mnt_opts) {
		/* first time security setup, copy sec_opts to fs_info */
		memcpy(&fs_info->security_opts, sec_opts, sizeof(*sec_opts));
	} else {
		/*
		 * Since SELinux (the only one supporting security_mnt_opts)
		 * does NOT support changing context during remount/mount of
		 * the same sb, this must be the same or part of the same
		 * security options, just free it.
		 */
		security_free_mnt_opts(sec_opts);
	}
#endif
	return ret;
}