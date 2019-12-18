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
struct super_block {int /*<<< orphan*/  s_umount; int /*<<< orphan*/  s_user_ns; } ;
struct fs_parameter {int dummy; } ;
struct fs_context {int /*<<< orphan*/  phase; TYPE_1__* root; } ;
struct TYPE_2__ {struct super_block* d_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EBUSY ; 
 int EPERM ; 
#define  FSCONFIG_CMD_CREATE 129 
#define  FSCONFIG_CMD_RECONFIGURE 128 
 int /*<<< orphan*/  FS_CONTEXT_AWAITING_MOUNT ; 
 int /*<<< orphan*/  FS_CONTEXT_CREATE_PARAMS ; 
 int /*<<< orphan*/  FS_CONTEXT_CREATING ; 
 int /*<<< orphan*/  FS_CONTEXT_FAILED ; 
 int /*<<< orphan*/  FS_CONTEXT_RECONFIGURING ; 
 int /*<<< orphan*/  FS_CONTEXT_RECONF_PARAMS ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fc_drop_locked (struct fs_context*) ; 
 int finish_clean_context (struct fs_context*) ; 
 int /*<<< orphan*/  mount_capable (struct fs_context*) ; 
 int /*<<< orphan*/  ns_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int reconfigure_super (struct fs_context*) ; 
 int security_sb_kern_mount (struct super_block*) ; 
 int /*<<< orphan*/  unlikely (int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfs_clean_context (struct fs_context*) ; 
 int vfs_get_tree (struct fs_context*) ; 
 int vfs_parse_fs_param (struct fs_context*,struct fs_parameter*) ; 

__attribute__((used)) static int vfs_fsconfig_locked(struct fs_context *fc, int cmd,
			       struct fs_parameter *param)
{
	struct super_block *sb;
	int ret;

	ret = finish_clean_context(fc);
	if (ret)
		return ret;
	switch (cmd) {
	case FSCONFIG_CMD_CREATE:
		if (fc->phase != FS_CONTEXT_CREATE_PARAMS)
			return -EBUSY;
		if (!mount_capable(fc))
			return -EPERM;
		fc->phase = FS_CONTEXT_CREATING;
		ret = vfs_get_tree(fc);
		if (ret)
			break;
		sb = fc->root->d_sb;
		ret = security_sb_kern_mount(sb);
		if (unlikely(ret)) {
			fc_drop_locked(fc);
			break;
		}
		up_write(&sb->s_umount);
		fc->phase = FS_CONTEXT_AWAITING_MOUNT;
		return 0;
	case FSCONFIG_CMD_RECONFIGURE:
		if (fc->phase != FS_CONTEXT_RECONF_PARAMS)
			return -EBUSY;
		fc->phase = FS_CONTEXT_RECONFIGURING;
		sb = fc->root->d_sb;
		if (!ns_capable(sb->s_user_ns, CAP_SYS_ADMIN)) {
			ret = -EPERM;
			break;
		}
		down_write(&sb->s_umount);
		ret = reconfigure_super(fc);
		up_write(&sb->s_umount);
		if (ret)
			break;
		vfs_clean_context(fc);
		return 0;
	default:
		if (fc->phase != FS_CONTEXT_CREATE_PARAMS &&
		    fc->phase != FS_CONTEXT_RECONF_PARAMS)
			return -EBUSY;

		return vfs_parse_fs_param(fc, param);
	}
	fc->phase = FS_CONTEXT_FAILED;
	return ret;
}