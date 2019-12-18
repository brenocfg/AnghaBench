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
typedef  scalar_t__ u64 ;
struct ufs_sb_private_info {int s_apbshift; unsigned int s_fpbshift; unsigned int s_apbmask; scalar_t__ fs_magic; scalar_t__ s_sbbase; scalar_t__ s_fpb; } ;
struct super_block {int dummy; } ;
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ctime; struct super_block* i_sb; } ;
struct buffer_head {scalar_t__ b_blocknr; scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  __fs64 ;
typedef  int /*<<< orphan*/  __fs32 ;
struct TYPE_2__ {struct ufs_sb_private_info* s_uspi; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ IS_SYNC (struct inode*) ; 
 scalar_t__ UFS2_MAGIC ; 
 int /*<<< orphan*/  UFSD (char*) ; 
 TYPE_1__* UFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 scalar_t__ fs32_to_cpu (struct super_block*,int /*<<< orphan*/ ) ; 
 scalar_t__ fs64_to_cpu (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 struct buffer_head* sb_bread (struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  sync_dirty_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  ufs_blknum (int /*<<< orphan*/ ) ; 
 scalar_t__ ufs_data_ptr_to_cpu (struct super_block*,void*) ; 
 scalar_t__ ufs_new_fragments (struct inode*,void*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int*,struct page*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u64
ufs_inode_getblock(struct inode *inode, u64 ind_block,
		  unsigned index, sector_t new_fragment, int *err,
		  int *new, struct page *locked_page)
{
	struct super_block *sb = inode->i_sb;
	struct ufs_sb_private_info *uspi = UFS_SB(sb)->s_uspi;
	int shift = uspi->s_apbshift - uspi->s_fpbshift;
	u64 tmp = 0, goal;
	struct buffer_head *bh;
	void *p;

	if (!ind_block)
		return 0;

	bh = sb_bread(sb, ind_block + (index >> shift));
	if (unlikely(!bh)) {
		*err = -EIO;
		return 0;
	}

	index &= uspi->s_apbmask >> uspi->s_fpbshift;
	if (uspi->fs_magic == UFS2_MAGIC)
		p = (__fs64 *)bh->b_data + index;
	else
		p = (__fs32 *)bh->b_data + index;

	tmp = ufs_data_ptr_to_cpu(sb, p);
	if (tmp)
		goto out;

	if (index && (uspi->fs_magic == UFS2_MAGIC ?
		      (tmp = fs64_to_cpu(sb, ((__fs64 *)bh->b_data)[index-1])) :
		      (tmp = fs32_to_cpu(sb, ((__fs32 *)bh->b_data)[index-1]))))
		goal = tmp + uspi->s_fpb;
	else
		goal = bh->b_blocknr + uspi->s_fpb;
	tmp = ufs_new_fragments(inode, p, ufs_blknum(new_fragment), goal,
				uspi->s_fpb, err, locked_page);
	if (!tmp)
		goto out;

	if (new)
		*new = 1;

	mark_buffer_dirty(bh);
	if (IS_SYNC(inode))
		sync_dirty_buffer(bh);
	inode->i_ctime = current_time(inode);
	mark_inode_dirty(inode);
out:
	brelse (bh);
	UFSD("EXIT\n");
	if (tmp)
		tmp += uspi->s_sbbase;
	return tmp;
}