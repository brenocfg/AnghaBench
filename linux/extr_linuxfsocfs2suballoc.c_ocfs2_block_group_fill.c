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
typedef  unsigned long long u64 ;
typedef  size_t u16 ;
struct super_block {int /*<<< orphan*/  s_blocksize; } ;
struct ocfs2_super {int /*<<< orphan*/  s_feature_incompat; int /*<<< orphan*/  fs_generation; } ;
struct ocfs2_group_desc {void* bg_bits; void* bg_free_bits_count; scalar_t__ bg_bitmap; void* bg_blkno; void* bg_parent_dinode; int /*<<< orphan*/  bg_next_group; void* bg_chain; void* bg_size; int /*<<< orphan*/  bg_generation; int /*<<< orphan*/  bg_signature; } ;
struct ocfs2_chain_list {void* cl_cpg; TYPE_1__* cl_recs; } ;
struct inode {struct super_block* i_sb; } ;
struct buffer_head {scalar_t__ b_blocknr; scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_4__ {unsigned long long ip_blkno; } ;
struct TYPE_3__ {int /*<<< orphan*/  c_blkno; } ;

/* Variables and functions */
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_GROUP_DESC_SIGNATURE ; 
 TYPE_2__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_CREATE ; 
 struct ocfs2_super* OCFS2_SB (struct super_block*) ; 
 void* cpu_to_le16 (unsigned int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le64 (unsigned long long) ; 
 unsigned int le16_to_cpu (void*) ; 
 int /*<<< orphan*/  memset (struct ocfs2_group_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_bg_discontig_add_extent (struct ocfs2_super*,struct ocfs2_group_desc*,struct ocfs2_chain_list*,unsigned long long,unsigned int) ; 
 unsigned int ocfs2_bits_per_group (struct ocfs2_chain_list*) ; 
 int ocfs2_error (struct super_block*,char*,unsigned long long,unsigned long long) ; 
 unsigned int ocfs2_group_bitmap_size (struct super_block*,int,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_access_gd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/  ocfs2_set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_block_group_fill(handle_t *handle,
				  struct inode *alloc_inode,
				  struct buffer_head *bg_bh,
				  u64 group_blkno,
				  unsigned int group_clusters,
				  u16 my_chain,
				  struct ocfs2_chain_list *cl)
{
	int status = 0;
	struct ocfs2_super *osb = OCFS2_SB(alloc_inode->i_sb);
	struct ocfs2_group_desc *bg = (struct ocfs2_group_desc *) bg_bh->b_data;
	struct super_block * sb = alloc_inode->i_sb;

	if (((unsigned long long) bg_bh->b_blocknr) != group_blkno) {
		status = ocfs2_error(alloc_inode->i_sb,
				     "group block (%llu) != b_blocknr (%llu)\n",
				     (unsigned long long)group_blkno,
				     (unsigned long long) bg_bh->b_blocknr);
		goto bail;
	}

	status = ocfs2_journal_access_gd(handle,
					 INODE_CACHE(alloc_inode),
					 bg_bh,
					 OCFS2_JOURNAL_ACCESS_CREATE);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	memset(bg, 0, sb->s_blocksize);
	strcpy(bg->bg_signature, OCFS2_GROUP_DESC_SIGNATURE);
	bg->bg_generation = cpu_to_le32(osb->fs_generation);
	bg->bg_size = cpu_to_le16(ocfs2_group_bitmap_size(sb, 1,
						osb->s_feature_incompat));
	bg->bg_chain = cpu_to_le16(my_chain);
	bg->bg_next_group = cl->cl_recs[my_chain].c_blkno;
	bg->bg_parent_dinode = cpu_to_le64(OCFS2_I(alloc_inode)->ip_blkno);
	bg->bg_blkno = cpu_to_le64(group_blkno);
	if (group_clusters == le16_to_cpu(cl->cl_cpg))
		bg->bg_bits = cpu_to_le16(ocfs2_bits_per_group(cl));
	else
		ocfs2_bg_discontig_add_extent(osb, bg, cl, group_blkno,
					      group_clusters);

	/* set the 1st bit in the bitmap to account for the descriptor block */
	ocfs2_set_bit(0, (unsigned long *)bg->bg_bitmap);
	bg->bg_free_bits_count = cpu_to_le16(le16_to_cpu(bg->bg_bits) - 1);

	ocfs2_journal_dirty(handle, bg_bh);

	/* There is no need to zero out or otherwise initialize the
	 * other blocks in a group - All valid FS metadata in a block
	 * group stores the superblock fs_generation value at
	 * allocation time. */

bail:
	if (status)
		mlog_errno(status);
	return status;
}