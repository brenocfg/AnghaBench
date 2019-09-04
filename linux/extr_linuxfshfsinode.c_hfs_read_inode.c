#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct inode {int i_mode; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; void* i_mtime; void* i_atime; void* i_ctime; int /*<<< orphan*/  i_size; void* i_ino; TYPE_2__* i_mapping; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_sb; } ;
struct hfs_sb_info {int s_file_umask; int s_dir_umask; int /*<<< orphan*/  s_gid; int /*<<< orphan*/  s_uid; } ;
struct hfs_iget_data {TYPE_4__* rec; int /*<<< orphan*/ * key; } ;
struct TYPE_9__ {int /*<<< orphan*/  MdDat; int /*<<< orphan*/  Val; int /*<<< orphan*/  DirID; } ;
struct TYPE_7__ {int Flags; int /*<<< orphan*/  MdDat; int /*<<< orphan*/  FlNum; int /*<<< orphan*/  ClpSize; int /*<<< orphan*/  RPyLen; int /*<<< orphan*/  RLgLen; int /*<<< orphan*/  RExtRec; int /*<<< orphan*/  PyLen; int /*<<< orphan*/  LgLen; int /*<<< orphan*/  ExtRec; } ;
struct TYPE_10__ {int type; TYPE_3__ dir; TYPE_1__ file; } ;
typedef  TYPE_4__ hfs_cat_rec ;
struct TYPE_12__ {int tz_secondswest; int /*<<< orphan*/  fs_blocks; int /*<<< orphan*/  flags; int /*<<< orphan*/  cat_key; int /*<<< orphan*/  open_dir_lock; int /*<<< orphan*/  open_dir_list; int /*<<< orphan*/  extents_lock; int /*<<< orphan*/ * rsrc_inode; } ;
struct TYPE_11__ {int tz_minuteswest; } ;
struct TYPE_8__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
#define  HFS_CDR_DIR 129 
#define  HFS_CDR_FIL 128 
 int HFS_FIL_LOCK ; 
 int /*<<< orphan*/  HFS_FLG_RSRC ; 
 TYPE_6__* HFS_I (struct inode*) ; 
 int /*<<< orphan*/  HFS_IS_RSRC (struct inode*) ; 
 struct hfs_sb_info* HFS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int S_IFDIR ; 
 int S_IFREG ; 
 int S_IRUGO ; 
 int S_IRWXUGO ; 
 int S_IWUGO ; 
 int S_IXUGO ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfs_aops ; 
 int /*<<< orphan*/  hfs_dir_inode_operations ; 
 int /*<<< orphan*/  hfs_dir_operations ; 
 int /*<<< orphan*/  hfs_file_inode_operations ; 
 int /*<<< orphan*/  hfs_file_operations ; 
 int /*<<< orphan*/  hfs_inode_read_fork (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfs_m_to_utime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 TYPE_5__ sys_tz ; 
 void* timespec_to_timespec64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hfs_read_inode(struct inode *inode, void *data)
{
	struct hfs_iget_data *idata = data;
	struct hfs_sb_info *hsb = HFS_SB(inode->i_sb);
	hfs_cat_rec *rec;

	HFS_I(inode)->flags = 0;
	HFS_I(inode)->rsrc_inode = NULL;
	mutex_init(&HFS_I(inode)->extents_lock);
	INIT_LIST_HEAD(&HFS_I(inode)->open_dir_list);
	spin_lock_init(&HFS_I(inode)->open_dir_lock);

	/* Initialize the inode */
	inode->i_uid = hsb->s_uid;
	inode->i_gid = hsb->s_gid;
	set_nlink(inode, 1);

	if (idata->key)
		HFS_I(inode)->cat_key = *idata->key;
	else
		HFS_I(inode)->flags |= HFS_FLG_RSRC;
	HFS_I(inode)->tz_secondswest = sys_tz.tz_minuteswest * 60;

	rec = idata->rec;
	switch (rec->type) {
	case HFS_CDR_FIL:
		if (!HFS_IS_RSRC(inode)) {
			hfs_inode_read_fork(inode, rec->file.ExtRec, rec->file.LgLen,
					    rec->file.PyLen, be16_to_cpu(rec->file.ClpSize));
		} else {
			hfs_inode_read_fork(inode, rec->file.RExtRec, rec->file.RLgLen,
					    rec->file.RPyLen, be16_to_cpu(rec->file.ClpSize));
		}

		inode->i_ino = be32_to_cpu(rec->file.FlNum);
		inode->i_mode = S_IRUGO | S_IXUGO;
		if (!(rec->file.Flags & HFS_FIL_LOCK))
			inode->i_mode |= S_IWUGO;
		inode->i_mode &= ~hsb->s_file_umask;
		inode->i_mode |= S_IFREG;
		inode->i_ctime = inode->i_atime = inode->i_mtime =
				timespec_to_timespec64(hfs_m_to_utime(rec->file.MdDat));
		inode->i_op = &hfs_file_inode_operations;
		inode->i_fop = &hfs_file_operations;
		inode->i_mapping->a_ops = &hfs_aops;
		break;
	case HFS_CDR_DIR:
		inode->i_ino = be32_to_cpu(rec->dir.DirID);
		inode->i_size = be16_to_cpu(rec->dir.Val) + 2;
		HFS_I(inode)->fs_blocks = 0;
		inode->i_mode = S_IFDIR | (S_IRWXUGO & ~hsb->s_dir_umask);
		inode->i_ctime = inode->i_atime = inode->i_mtime =
				timespec_to_timespec64(hfs_m_to_utime(rec->dir.MdDat));
		inode->i_op = &hfs_dir_inode_operations;
		inode->i_fop = &hfs_dir_operations;
		break;
	default:
		make_bad_inode(inode);
	}
	return 0;
}