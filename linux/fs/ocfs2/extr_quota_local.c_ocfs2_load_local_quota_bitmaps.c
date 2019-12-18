#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ocfs2_quota_chunk {int qc_num; int /*<<< orphan*/  qc_chunk; int /*<<< orphan*/ * qc_headerbh; } ;
struct ocfs2_local_disk_dqinfo {int /*<<< orphan*/  dqi_chunks; } ;
struct list_head {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 struct ocfs2_quota_chunk* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct ocfs2_quota_chunk*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_qf_chunk_cachep ; 
 int ocfs2_read_quota_block (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ocfs2_release_local_quota_bitmaps (struct list_head*) ; 
 int /*<<< orphan*/  ol_quota_chunk_block (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ocfs2_load_local_quota_bitmaps(struct inode *inode,
			struct ocfs2_local_disk_dqinfo *ldinfo,
			struct list_head *head)
{
	struct ocfs2_quota_chunk *newchunk;
	int i, status;

	INIT_LIST_HEAD(head);
	for (i = 0; i < le32_to_cpu(ldinfo->dqi_chunks); i++) {
		newchunk = kmem_cache_alloc(ocfs2_qf_chunk_cachep, GFP_NOFS);
		if (!newchunk) {
			ocfs2_release_local_quota_bitmaps(head);
			return -ENOMEM;
		}
		newchunk->qc_num = i;
		newchunk->qc_headerbh = NULL;
		status = ocfs2_read_quota_block(inode,
				ol_quota_chunk_block(inode->i_sb, i),
				&newchunk->qc_headerbh);
		if (status) {
			mlog_errno(status);
			kmem_cache_free(ocfs2_qf_chunk_cachep, newchunk);
			ocfs2_release_local_quota_bitmaps(head);
			return status;
		}
		list_add_tail(&newchunk->qc_chunk, head);
	}
	return 0;
}