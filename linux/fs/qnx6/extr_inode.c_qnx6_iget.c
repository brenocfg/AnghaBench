#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uid_t ;
typedef  int u32 ;
struct super_block {int /*<<< orphan*/  s_id; } ;
struct qnx6_sb_info {TYPE_1__* inodes; } ;
struct qnx6_inode_info {int /*<<< orphan*/  di_filelevels; int /*<<< orphan*/  di_block_ptr; } ;
struct qnx6_inode_entry {int /*<<< orphan*/  di_filelevels; int /*<<< orphan*/  di_block_ptr; int /*<<< orphan*/  di_ctime; int /*<<< orphan*/  di_atime; int /*<<< orphan*/  di_mtime; int /*<<< orphan*/  di_size; int /*<<< orphan*/  di_gid; int /*<<< orphan*/  di_uid; int /*<<< orphan*/  di_mode; } ;
struct page {int dummy; } ;
struct TYPE_9__ {scalar_t__ tv_nsec; void* tv_sec; } ;
struct TYPE_8__ {scalar_t__ tv_nsec; void* tv_sec; } ;
struct TYPE_7__ {scalar_t__ tv_nsec; void* tv_sec; } ;
struct inode {int i_state; int i_size; int i_blocks; scalar_t__ i_mode; TYPE_5__* i_mapping; int /*<<< orphan*/ * i_op; int /*<<< orphan*/ * i_fop; TYPE_4__ i_ctime; TYPE_3__ i_atime; TYPE_2__ i_mtime; } ;
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  gid_t ;
struct TYPE_10__ {int /*<<< orphan*/ * a_ops; } ;
struct TYPE_6__ {struct address_space* i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct inode* ERR_CAST (struct page*) ; 
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int I_NEW ; 
 unsigned int PAGE_MASK ; 
 unsigned int PAGE_SHIFT ; 
 struct qnx6_inode_info* QNX6_I (struct inode*) ; 
 unsigned int QNX6_INODE_SIZE_BITS ; 
 struct qnx6_sb_info* QNX6_SB (struct super_block*) ; 
 scalar_t__ S_ISDIR (scalar_t__) ; 
 scalar_t__ S_ISLNK (scalar_t__) ; 
 scalar_t__ S_ISREG (scalar_t__) ; 
 scalar_t__ fs16_to_cpu (struct qnx6_sb_info*,int /*<<< orphan*/ ) ; 
 void* fs32_to_cpu (struct qnx6_sb_info*,int /*<<< orphan*/ ) ; 
 int fs64_to_cpu (struct qnx6_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_ro_fops ; 
 int /*<<< orphan*/  i_gid_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_uid_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iget_failed (struct inode*) ; 
 struct inode* iget_locked (struct super_block*,unsigned int) ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_nohighmem (struct inode*) ; 
 int /*<<< orphan*/  kmap (struct page*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ page_address (struct page*) ; 
 int /*<<< orphan*/  page_symlink_inode_operations ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  qnx6_aops ; 
 int /*<<< orphan*/  qnx6_dir_inode_operations ; 
 int /*<<< orphan*/  qnx6_dir_operations ; 
 int /*<<< orphan*/  qnx6_put_page (struct page*) ; 
 struct page* read_mapping_page (struct address_space*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

struct inode *qnx6_iget(struct super_block *sb, unsigned ino)
{
	struct qnx6_sb_info *sbi = QNX6_SB(sb);
	struct qnx6_inode_entry *raw_inode;
	struct inode *inode;
	struct qnx6_inode_info	*ei;
	struct address_space *mapping;
	struct page *page;
	u32 n, offs;

	inode = iget_locked(sb, ino);
	if (!inode)
		return ERR_PTR(-ENOMEM);
	if (!(inode->i_state & I_NEW))
		return inode;

	ei = QNX6_I(inode);

	inode->i_mode = 0;

	if (ino == 0) {
		pr_err("bad inode number on dev %s: %u is out of range\n",
		       sb->s_id, ino);
		iget_failed(inode);
		return ERR_PTR(-EIO);
	}
	n = (ino - 1) >> (PAGE_SHIFT - QNX6_INODE_SIZE_BITS);
	offs = (ino - 1) & (~PAGE_MASK >> QNX6_INODE_SIZE_BITS);
	mapping = sbi->inodes->i_mapping;
	page = read_mapping_page(mapping, n, NULL);
	if (IS_ERR(page)) {
		pr_err("major problem: unable to read inode from dev %s\n",
		       sb->s_id);
		iget_failed(inode);
		return ERR_CAST(page);
	}
	kmap(page);
	raw_inode = ((struct qnx6_inode_entry *)page_address(page)) + offs;

	inode->i_mode    = fs16_to_cpu(sbi, raw_inode->di_mode);
	i_uid_write(inode, (uid_t)fs32_to_cpu(sbi, raw_inode->di_uid));
	i_gid_write(inode, (gid_t)fs32_to_cpu(sbi, raw_inode->di_gid));
	inode->i_size    = fs64_to_cpu(sbi, raw_inode->di_size);
	inode->i_mtime.tv_sec   = fs32_to_cpu(sbi, raw_inode->di_mtime);
	inode->i_mtime.tv_nsec = 0;
	inode->i_atime.tv_sec   = fs32_to_cpu(sbi, raw_inode->di_atime);
	inode->i_atime.tv_nsec = 0;
	inode->i_ctime.tv_sec   = fs32_to_cpu(sbi, raw_inode->di_ctime);
	inode->i_ctime.tv_nsec = 0;

	/* calc blocks based on 512 byte blocksize */
	inode->i_blocks = (inode->i_size + 511) >> 9;

	memcpy(&ei->di_block_ptr, &raw_inode->di_block_ptr,
				sizeof(raw_inode->di_block_ptr));
	ei->di_filelevels = raw_inode->di_filelevels;

	if (S_ISREG(inode->i_mode)) {
		inode->i_fop = &generic_ro_fops;
		inode->i_mapping->a_ops = &qnx6_aops;
	} else if (S_ISDIR(inode->i_mode)) {
		inode->i_op = &qnx6_dir_inode_operations;
		inode->i_fop = &qnx6_dir_operations;
		inode->i_mapping->a_ops = &qnx6_aops;
	} else if (S_ISLNK(inode->i_mode)) {
		inode->i_op = &page_symlink_inode_operations;
		inode_nohighmem(inode);
		inode->i_mapping->a_ops = &qnx6_aops;
	} else
		init_special_inode(inode, inode->i_mode, 0);
	qnx6_put_page(page);
	unlock_new_inode(inode);
	return inode;
}