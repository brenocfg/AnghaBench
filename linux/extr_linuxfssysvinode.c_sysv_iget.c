#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  u8 ;
struct sysv_sb_info {unsigned int s_ninodes; } ;
struct sysv_inode_info {int /*<<< orphan*/ * i_data; scalar_t__ i_dir_start_lookup; } ;
struct sysv_inode {int /*<<< orphan*/ * i_data; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_nlink; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_mode; } ;
struct super_block {int /*<<< orphan*/  s_id; } ;
struct TYPE_8__ {scalar_t__ tv_nsec; void* tv_sec; } ;
struct TYPE_7__ {scalar_t__ tv_nsec; void* tv_sec; } ;
struct TYPE_6__ {scalar_t__ tv_nsec; void* tv_sec; } ;
struct inode {int i_state; scalar_t__ i_mode; scalar_t__ i_blocks; TYPE_4__ i_mtime; TYPE_3__ i_atime; TYPE_2__ i_ctime; void* i_size; TYPE_1__* i_sb; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  gid_t ;
struct TYPE_5__ {int /*<<< orphan*/  s_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 int I_NEW ; 
 struct sysv_inode_info* SYSV_I (struct inode*) ; 
 struct sysv_sb_info* SYSV_SB (struct super_block*) ; 
 scalar_t__ S_ISBLK (scalar_t__) ; 
 scalar_t__ S_ISCHR (scalar_t__) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ fs16_to_cpu (struct sysv_sb_info*,int /*<<< orphan*/ ) ; 
 void* fs32_to_cpu (struct sysv_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_gid_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_uid_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iget_failed (struct inode*) ; 
 struct inode* iget_locked (struct super_block*,unsigned int) ; 
 int /*<<< orphan*/  old_decode_dev (void*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  read3byte (struct sysv_sb_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,scalar_t__) ; 
 struct sysv_inode* sysv_raw_inode (struct super_block*,unsigned int,struct buffer_head**) ; 
 int /*<<< orphan*/  sysv_set_inode (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

struct inode *sysv_iget(struct super_block *sb, unsigned int ino)
{
	struct sysv_sb_info * sbi = SYSV_SB(sb);
	struct buffer_head * bh;
	struct sysv_inode * raw_inode;
	struct sysv_inode_info * si;
	struct inode *inode;
	unsigned int block;

	if (!ino || ino > sbi->s_ninodes) {
		printk("Bad inode number on dev %s: %d is out of range\n",
		       sb->s_id, ino);
		return ERR_PTR(-EIO);
	}

	inode = iget_locked(sb, ino);
	if (!inode)
		return ERR_PTR(-ENOMEM);
	if (!(inode->i_state & I_NEW))
		return inode;

	raw_inode = sysv_raw_inode(sb, ino, &bh);
	if (!raw_inode) {
		printk("Major problem: unable to read inode from dev %s\n",
		       inode->i_sb->s_id);
		goto bad_inode;
	}
	/* SystemV FS: kludge permissions if ino==SYSV_ROOT_INO ?? */
	inode->i_mode = fs16_to_cpu(sbi, raw_inode->i_mode);
	i_uid_write(inode, (uid_t)fs16_to_cpu(sbi, raw_inode->i_uid));
	i_gid_write(inode, (gid_t)fs16_to_cpu(sbi, raw_inode->i_gid));
	set_nlink(inode, fs16_to_cpu(sbi, raw_inode->i_nlink));
	inode->i_size = fs32_to_cpu(sbi, raw_inode->i_size);
	inode->i_atime.tv_sec = fs32_to_cpu(sbi, raw_inode->i_atime);
	inode->i_mtime.tv_sec = fs32_to_cpu(sbi, raw_inode->i_mtime);
	inode->i_ctime.tv_sec = fs32_to_cpu(sbi, raw_inode->i_ctime);
	inode->i_ctime.tv_nsec = 0;
	inode->i_atime.tv_nsec = 0;
	inode->i_mtime.tv_nsec = 0;
	inode->i_blocks = 0;

	si = SYSV_I(inode);
	for (block = 0; block < 10+1+1+1; block++)
		read3byte(sbi, &raw_inode->i_data[3*block],
				(u8 *)&si->i_data[block]);
	brelse(bh);
	si->i_dir_start_lookup = 0;
	if (S_ISCHR(inode->i_mode) || S_ISBLK(inode->i_mode))
		sysv_set_inode(inode,
			       old_decode_dev(fs32_to_cpu(sbi, si->i_data[0])));
	else
		sysv_set_inode(inode, 0);
	unlock_new_inode(inode);
	return inode;

bad_inode:
	iget_failed(inode);
	return ERR_PTR(-EIO);
}