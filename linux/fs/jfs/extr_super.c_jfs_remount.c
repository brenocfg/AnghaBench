#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int s_flags; } ;
typedef  scalar_t__ s64 ;
struct TYPE_4__ {int flag; TYPE_1__* direct_inode; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int EINVAL ; 
 int EROFS ; 
 int JFS_NOINTEGRITY ; 
 TYPE_2__* JFS_SBI (struct super_block*) ; 
 int SB_RDONLY ; 
 int /*<<< orphan*/  dquot_resume (struct super_block*,int) ; 
 int dquot_suspend (struct super_block*,int) ; 
 int jfs_extendfs (struct super_block*,scalar_t__,int /*<<< orphan*/ ) ; 
 int jfs_mount_rw (struct super_block*,int) ; 
 int jfs_umount_rw (struct super_block*) ; 
 int /*<<< orphan*/  parse_options (char*,struct super_block*,scalar_t__*,int*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ sb_rdonly (struct super_block*) ; 
 int /*<<< orphan*/  sync_filesystem (struct super_block*) ; 
 int /*<<< orphan*/  truncate_inode_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jfs_remount(struct super_block *sb, int *flags, char *data)
{
	s64 newLVSize = 0;
	int rc = 0;
	int flag = JFS_SBI(sb)->flag;
	int ret;

	sync_filesystem(sb);
	if (!parse_options(data, sb, &newLVSize, &flag))
		return -EINVAL;

	if (newLVSize) {
		if (sb_rdonly(sb)) {
			pr_err("JFS: resize requires volume to be mounted read-write\n");
			return -EROFS;
		}
		rc = jfs_extendfs(sb, newLVSize, 0);
		if (rc)
			return rc;
	}

	if (sb_rdonly(sb) && !(*flags & SB_RDONLY)) {
		/*
		 * Invalidate any previously read metadata.  fsck may have
		 * changed the on-disk data since we mounted r/o
		 */
		truncate_inode_pages(JFS_SBI(sb)->direct_inode->i_mapping, 0);

		JFS_SBI(sb)->flag = flag;
		ret = jfs_mount_rw(sb, 1);

		/* mark the fs r/w for quota activity */
		sb->s_flags &= ~SB_RDONLY;

		dquot_resume(sb, -1);
		return ret;
	}
	if (!sb_rdonly(sb) && (*flags & SB_RDONLY)) {
		rc = dquot_suspend(sb, -1);
		if (rc < 0)
			return rc;
		rc = jfs_umount_rw(sb);
		JFS_SBI(sb)->flag = flag;
		return rc;
	}
	if ((JFS_SBI(sb)->flag & JFS_NOINTEGRITY) != (flag & JFS_NOINTEGRITY))
		if (!sb_rdonly(sb)) {
			rc = jfs_umount_rw(sb);
			if (rc)
				return rc;

			JFS_SBI(sb)->flag = flag;
			ret = jfs_mount_rw(sb, 1);
			return ret;
		}
	JFS_SBI(sb)->flag = flag;

	return 0;
}