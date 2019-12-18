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
struct inode {int i_mode; int /*<<< orphan*/  i_blocks; int /*<<< orphan*/  i_size; void* i_ctime; void* i_mtime; void* i_atime; int /*<<< orphan*/  i_ino; TYPE_1__* i_mapping; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; } ;
struct hostfs_stat {int mode; int /*<<< orphan*/  blocks; int /*<<< orphan*/  size; int /*<<< orphan*/  ctime; int /*<<< orphan*/  mtime; int /*<<< orphan*/  atime; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  nlink; int /*<<< orphan*/  ino; int /*<<< orphan*/  min; int /*<<< orphan*/  maj; } ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_2__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  S_IFBLK 134 
#define  S_IFCHR 133 
#define  S_IFDIR 132 
#define  S_IFIFO 131 
#define  S_IFLNK 130 
 int S_IFMT ; 
#define  S_IFREG 129 
#define  S_IFSOCK 128 
 int /*<<< orphan*/  hostfs_aops ; 
 int /*<<< orphan*/  hostfs_dir_fops ; 
 int /*<<< orphan*/  hostfs_dir_iops ; 
 int /*<<< orphan*/  hostfs_file_fops ; 
 int /*<<< orphan*/  hostfs_iops ; 
 int /*<<< orphan*/  hostfs_link_iops ; 
 int /*<<< orphan*/  i_gid_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_uid_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int /*<<< orphan*/ ) ; 
 int stat_file (char*,struct hostfs_stat*,int) ; 
 void* timespec_to_timespec64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_name(struct inode *ino, char *name)
{
	dev_t rdev;
	struct hostfs_stat st;
	int err = stat_file(name, &st, -1);
	if (err)
		return err;

	/* Reencode maj and min with the kernel encoding.*/
	rdev = MKDEV(st.maj, st.min);

	switch (st.mode & S_IFMT) {
	case S_IFLNK:
		ino->i_op = &hostfs_link_iops;
		break;
	case S_IFDIR:
		ino->i_op = &hostfs_dir_iops;
		ino->i_fop = &hostfs_dir_fops;
		break;
	case S_IFCHR:
	case S_IFBLK:
	case S_IFIFO:
	case S_IFSOCK:
		init_special_inode(ino, st.mode & S_IFMT, rdev);
		ino->i_op = &hostfs_iops;
		break;
	case S_IFREG:
		ino->i_op = &hostfs_iops;
		ino->i_fop = &hostfs_file_fops;
		ino->i_mapping->a_ops = &hostfs_aops;
		break;
	default:
		return -EIO;
	}

	ino->i_ino = st.ino;
	ino->i_mode = st.mode;
	set_nlink(ino, st.nlink);
	i_uid_write(ino, st.uid);
	i_gid_write(ino, st.gid);
	ino->i_atime = timespec_to_timespec64(st.atime);
	ino->i_mtime = timespec_to_timespec64(st.mtime);
	ino->i_ctime = timespec_to_timespec64(st.ctime);
	ino->i_size = st.size;
	ino->i_blocks = st.blocks;
	return 0;
}