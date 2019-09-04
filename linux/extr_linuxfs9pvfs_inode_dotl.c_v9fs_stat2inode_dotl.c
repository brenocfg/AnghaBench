#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int umode_t ;
struct v9fs_inode {int /*<<< orphan*/  cache_validity; } ;
struct p9_stat_dotl {int st_result_mask; int st_mode; int /*<<< orphan*/  st_gen; int /*<<< orphan*/  st_blocks; int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_rdev; int /*<<< orphan*/  st_nlink; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_ctime_nsec; int /*<<< orphan*/  st_ctime_sec; int /*<<< orphan*/  st_mtime_nsec; int /*<<< orphan*/  st_mtime_sec; int /*<<< orphan*/  st_atime_nsec; int /*<<< orphan*/  st_atime_sec; } ;
struct TYPE_6__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_5__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_4__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct inode {int i_mode; int /*<<< orphan*/  i_generation; int /*<<< orphan*/  i_blocks; int /*<<< orphan*/  i_rdev; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; TYPE_3__ i_ctime; TYPE_2__ i_mtime; TYPE_1__ i_atime; } ;

/* Variables and functions */
 int P9_STATS_ATIME ; 
 int P9_STATS_BASIC ; 
 int P9_STATS_BLOCKS ; 
 int P9_STATS_CTIME ; 
 int P9_STATS_GEN ; 
 int P9_STATS_GID ; 
 int P9_STATS_MODE ; 
 int P9_STATS_MTIME ; 
 int P9_STATS_NLINK ; 
 int P9_STATS_RDEV ; 
 int P9_STATS_SIZE ; 
 int P9_STATS_UID ; 
 int S_IALLUGO ; 
 scalar_t__ S_ISBLK (int) ; 
 scalar_t__ S_ISCHR (int) ; 
 struct v9fs_inode* V9FS_I (struct inode*) ; 
 int /*<<< orphan*/  V9FS_INO_INVALID_ATTR ; 
 unsigned int V9FS_STAT2INODE_KEEP_ISIZE ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_decode_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v9fs_i_size_write (struct inode*,int /*<<< orphan*/ ) ; 

void
v9fs_stat2inode_dotl(struct p9_stat_dotl *stat, struct inode *inode,
		      unsigned int flags)
{
	umode_t mode;
	struct v9fs_inode *v9inode = V9FS_I(inode);

	if ((stat->st_result_mask & P9_STATS_BASIC) == P9_STATS_BASIC) {
		inode->i_atime.tv_sec = stat->st_atime_sec;
		inode->i_atime.tv_nsec = stat->st_atime_nsec;
		inode->i_mtime.tv_sec = stat->st_mtime_sec;
		inode->i_mtime.tv_nsec = stat->st_mtime_nsec;
		inode->i_ctime.tv_sec = stat->st_ctime_sec;
		inode->i_ctime.tv_nsec = stat->st_ctime_nsec;
		inode->i_uid = stat->st_uid;
		inode->i_gid = stat->st_gid;
		set_nlink(inode, stat->st_nlink);

		mode = stat->st_mode & S_IALLUGO;
		mode |= inode->i_mode & ~S_IALLUGO;
		inode->i_mode = mode;

		if (!(flags & V9FS_STAT2INODE_KEEP_ISIZE))
			v9fs_i_size_write(inode, stat->st_size);
		inode->i_blocks = stat->st_blocks;
	} else {
		if (stat->st_result_mask & P9_STATS_ATIME) {
			inode->i_atime.tv_sec = stat->st_atime_sec;
			inode->i_atime.tv_nsec = stat->st_atime_nsec;
		}
		if (stat->st_result_mask & P9_STATS_MTIME) {
			inode->i_mtime.tv_sec = stat->st_mtime_sec;
			inode->i_mtime.tv_nsec = stat->st_mtime_nsec;
		}
		if (stat->st_result_mask & P9_STATS_CTIME) {
			inode->i_ctime.tv_sec = stat->st_ctime_sec;
			inode->i_ctime.tv_nsec = stat->st_ctime_nsec;
		}
		if (stat->st_result_mask & P9_STATS_UID)
			inode->i_uid = stat->st_uid;
		if (stat->st_result_mask & P9_STATS_GID)
			inode->i_gid = stat->st_gid;
		if (stat->st_result_mask & P9_STATS_NLINK)
			set_nlink(inode, stat->st_nlink);
		if (stat->st_result_mask & P9_STATS_MODE) {
			inode->i_mode = stat->st_mode;
			if ((S_ISBLK(inode->i_mode)) ||
						(S_ISCHR(inode->i_mode)))
				init_special_inode(inode, inode->i_mode,
								inode->i_rdev);
		}
		if (stat->st_result_mask & P9_STATS_RDEV)
			inode->i_rdev = new_decode_dev(stat->st_rdev);
		if (!(flags & V9FS_STAT2INODE_KEEP_ISIZE) &&
		    stat->st_result_mask & P9_STATS_SIZE)
			v9fs_i_size_write(inode, stat->st_size);
		if (stat->st_result_mask & P9_STATS_BLOCKS)
			inode->i_blocks = stat->st_blocks;
	}
	if (stat->st_result_mask & P9_STATS_GEN)
		inode->i_generation = stat->st_gen;

	/* Currently we don't support P9_STATS_BTIME and P9_STATS_DATA_VERSION
	 * because the inode structure does not have fields for them.
	 */
	v9inode->cache_validity &= ~V9FS_INO_INVALID_ATTR;
}