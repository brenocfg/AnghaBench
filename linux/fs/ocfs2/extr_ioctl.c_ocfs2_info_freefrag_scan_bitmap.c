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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct ocfs2_super {int dummy; } ;
struct ocfs2_info_freefrag_stats {int dummy; } ;
struct TYPE_8__ {unsigned int ffs_min; void* ffs_clusters; int ffs_free_chunks_real; int ffs_avg; void* ffs_free_clusters; } ;
struct ocfs2_info_freefrag {int iff_chunksize; TYPE_4__ iff_ffs; int /*<<< orphan*/  iff_req; } ;
struct TYPE_6__ {int /*<<< orphan*/  i_used; int /*<<< orphan*/  i_total; } ;
struct TYPE_7__ {TYPE_2__ bitmap1; } ;
struct ocfs2_chain_list {struct ocfs2_chain_rec* cl_recs; int /*<<< orphan*/  cl_next_free_rec; int /*<<< orphan*/  cl_cpg; } ;
struct TYPE_5__ {struct ocfs2_chain_list i_chain; } ;
struct ocfs2_dinode {TYPE_3__ id1; TYPE_1__ id2; } ;
struct ocfs2_chain_rec {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 scalar_t__ o2info_coherent (int /*<<< orphan*/ *) ; 
 int ocfs2_info_freefrag_scan_chain (struct ocfs2_super*,struct inode*,struct ocfs2_dinode*,struct ocfs2_chain_rec*,struct ocfs2_info_freefrag*,int) ; 
 int ocfs2_inode_lock (struct inode*,struct buffer_head**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int /*<<< orphan*/ ) ; 
 int ocfs2_read_blocks_sync (struct ocfs2_super*,int /*<<< orphan*/ ,int,struct buffer_head**) ; 

__attribute__((used)) static int ocfs2_info_freefrag_scan_bitmap(struct ocfs2_super *osb,
					   struct inode *gb_inode, u64 blkno,
					   struct ocfs2_info_freefrag *ffg)
{
	u32 chunks_in_group;
	int status = 0, unlock = 0, i;

	struct buffer_head *bh = NULL;
	struct ocfs2_chain_list *cl = NULL;
	struct ocfs2_chain_rec *rec = NULL;
	struct ocfs2_dinode *gb_dinode = NULL;

	if (gb_inode)
		inode_lock(gb_inode);

	if (o2info_coherent(&ffg->iff_req)) {
		status = ocfs2_inode_lock(gb_inode, &bh, 0);
		if (status < 0) {
			mlog_errno(status);
			goto bail;
		}
		unlock = 1;
	} else {
		status = ocfs2_read_blocks_sync(osb, blkno, 1, &bh);
		if (status < 0) {
			mlog_errno(status);
			goto bail;
		}
	}

	gb_dinode = (struct ocfs2_dinode *)bh->b_data;
	cl = &(gb_dinode->id2.i_chain);

	/*
	 * Chunksize(in) clusters from userspace should be
	 * less than clusters in a group.
	 */
	if (ffg->iff_chunksize > le16_to_cpu(cl->cl_cpg)) {
		status = -EINVAL;
		goto bail;
	}

	memset(&ffg->iff_ffs, 0, sizeof(struct ocfs2_info_freefrag_stats));

	ffg->iff_ffs.ffs_min = ~0U;
	ffg->iff_ffs.ffs_clusters =
			le32_to_cpu(gb_dinode->id1.bitmap1.i_total);
	ffg->iff_ffs.ffs_free_clusters = ffg->iff_ffs.ffs_clusters -
			le32_to_cpu(gb_dinode->id1.bitmap1.i_used);

	chunks_in_group = le16_to_cpu(cl->cl_cpg) / ffg->iff_chunksize + 1;

	for (i = 0; i < le16_to_cpu(cl->cl_next_free_rec); i++) {
		rec = &(cl->cl_recs[i]);
		status = ocfs2_info_freefrag_scan_chain(osb, gb_inode,
							gb_dinode,
							rec, ffg,
							chunks_in_group);
		if (status)
			goto bail;
	}

	if (ffg->iff_ffs.ffs_free_chunks_real)
		ffg->iff_ffs.ffs_avg = (ffg->iff_ffs.ffs_avg /
					ffg->iff_ffs.ffs_free_chunks_real);
bail:
	if (unlock)
		ocfs2_inode_unlock(gb_inode, 0);

	if (gb_inode)
		inode_unlock(gb_inode);

	iput(gb_inode);
	brelse(bh);

	return status;
}