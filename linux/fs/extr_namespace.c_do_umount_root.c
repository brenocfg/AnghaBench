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
struct super_block {int /*<<< orphan*/  s_umount; int /*<<< orphan*/  s_root; } ;
struct fs_context {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct fs_context*) ; 
 int PTR_ERR (struct fs_context*) ; 
 int /*<<< orphan*/  SB_RDONLY ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 struct fs_context* fs_context_for_reconfigure (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int parse_monolithic_mount_data (struct fs_context*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_fs_context (struct fs_context*) ; 
 int reconfigure_super (struct fs_context*) ; 
 int /*<<< orphan*/  sb_rdonly (struct super_block*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_umount_root(struct super_block *sb)
{
	int ret = 0;

	down_write(&sb->s_umount);
	if (!sb_rdonly(sb)) {
		struct fs_context *fc;

		fc = fs_context_for_reconfigure(sb->s_root, SB_RDONLY,
						SB_RDONLY);
		if (IS_ERR(fc)) {
			ret = PTR_ERR(fc);
		} else {
			ret = parse_monolithic_mount_data(fc, NULL);
			if (!ret)
				ret = reconfigure_super(fc);
			put_fs_context(fc);
		}
	}
	up_write(&sb->s_umount);
	return ret;
}