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
typedef  int umode_t ;
struct v9fs_session_info {int /*<<< orphan*/  cache; } ;
struct inode {int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_rdev; int /*<<< orphan*/  i_mode; TYPE_1__* i_mapping; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; scalar_t__ i_blocks; } ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_2__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_FSCACHE ; 
 int /*<<< orphan*/  CACHE_LOOSE ; 
 int /*<<< orphan*/  CACHE_MMAP ; 
 int EINVAL ; 
 int /*<<< orphan*/  P9_DEBUG_ERROR ; 
#define  S_IFBLK 134 
#define  S_IFCHR 133 
#define  S_IFDIR 132 
#define  S_IFIFO 131 
#define  S_IFLNK 130 
 int S_IFMT ; 
#define  S_IFREG 129 
#define  S_IFSOCK 128 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_init_owner (struct inode*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  v9fs_addr_operations ; 
 int /*<<< orphan*/  v9fs_cached_file_operations ; 
 int /*<<< orphan*/  v9fs_cached_file_operations_dotl ; 
 int /*<<< orphan*/  v9fs_dir_inode_operations ; 
 int /*<<< orphan*/  v9fs_dir_inode_operations_dotl ; 
 int /*<<< orphan*/  v9fs_dir_inode_operations_dotu ; 
 int /*<<< orphan*/  v9fs_dir_operations ; 
 int /*<<< orphan*/  v9fs_dir_operations_dotl ; 
 int /*<<< orphan*/  v9fs_file_inode_operations ; 
 int /*<<< orphan*/  v9fs_file_inode_operations_dotl ; 
 int /*<<< orphan*/  v9fs_file_operations ; 
 int /*<<< orphan*/  v9fs_file_operations_dotl ; 
 int /*<<< orphan*/  v9fs_mmap_file_operations ; 
 int /*<<< orphan*/  v9fs_mmap_file_operations_dotl ; 
 int /*<<< orphan*/  v9fs_proto_dotl (struct v9fs_session_info*) ; 
 int /*<<< orphan*/  v9fs_proto_dotu (struct v9fs_session_info*) ; 
 int /*<<< orphan*/  v9fs_symlink_inode_operations ; 
 int /*<<< orphan*/  v9fs_symlink_inode_operations_dotl ; 

int v9fs_init_inode(struct v9fs_session_info *v9ses,
		    struct inode *inode, umode_t mode, dev_t rdev)
{
	int err = 0;

	inode_init_owner(inode, NULL, mode);
	inode->i_blocks = 0;
	inode->i_rdev = rdev;
	inode->i_atime = inode->i_mtime = inode->i_ctime = current_time(inode);
	inode->i_mapping->a_ops = &v9fs_addr_operations;

	switch (mode & S_IFMT) {
	case S_IFIFO:
	case S_IFBLK:
	case S_IFCHR:
	case S_IFSOCK:
		if (v9fs_proto_dotl(v9ses)) {
			inode->i_op = &v9fs_file_inode_operations_dotl;
		} else if (v9fs_proto_dotu(v9ses)) {
			inode->i_op = &v9fs_file_inode_operations;
		} else {
			p9_debug(P9_DEBUG_ERROR,
				 "special files without extended mode\n");
			err = -EINVAL;
			goto error;
		}
		init_special_inode(inode, inode->i_mode, inode->i_rdev);
		break;
	case S_IFREG:
		if (v9fs_proto_dotl(v9ses)) {
			inode->i_op = &v9fs_file_inode_operations_dotl;
			if (v9ses->cache == CACHE_LOOSE ||
			    v9ses->cache == CACHE_FSCACHE)
				inode->i_fop =
					&v9fs_cached_file_operations_dotl;
			else if (v9ses->cache == CACHE_MMAP)
				inode->i_fop = &v9fs_mmap_file_operations_dotl;
			else
				inode->i_fop = &v9fs_file_operations_dotl;
		} else {
			inode->i_op = &v9fs_file_inode_operations;
			if (v9ses->cache == CACHE_LOOSE ||
			    v9ses->cache == CACHE_FSCACHE)
				inode->i_fop =
					&v9fs_cached_file_operations;
			else if (v9ses->cache == CACHE_MMAP)
				inode->i_fop = &v9fs_mmap_file_operations;
			else
				inode->i_fop = &v9fs_file_operations;
		}

		break;
	case S_IFLNK:
		if (!v9fs_proto_dotu(v9ses) && !v9fs_proto_dotl(v9ses)) {
			p9_debug(P9_DEBUG_ERROR,
				 "extended modes used with legacy protocol\n");
			err = -EINVAL;
			goto error;
		}

		if (v9fs_proto_dotl(v9ses))
			inode->i_op = &v9fs_symlink_inode_operations_dotl;
		else
			inode->i_op = &v9fs_symlink_inode_operations;

		break;
	case S_IFDIR:
		inc_nlink(inode);
		if (v9fs_proto_dotl(v9ses))
			inode->i_op = &v9fs_dir_inode_operations_dotl;
		else if (v9fs_proto_dotu(v9ses))
			inode->i_op = &v9fs_dir_inode_operations_dotu;
		else
			inode->i_op = &v9fs_dir_inode_operations;

		if (v9fs_proto_dotl(v9ses))
			inode->i_fop = &v9fs_dir_operations_dotl;
		else
			inode->i_fop = &v9fs_dir_operations;

		break;
	default:
		p9_debug(P9_DEBUG_ERROR, "BAD mode 0x%hx S_IFMT 0x%x\n",
			 mode, mode & S_IFMT);
		err = -EINVAL;
		goto error;
	}
error:
	return err;

}