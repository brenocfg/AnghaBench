#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ocfs2_super {TYPE_2__* sb; int /*<<< orphan*/  fs_generation; } ;
struct ocfs2_extent_tree {int /*<<< orphan*/  et_ci; } ;
struct TYPE_4__ {void* l_count; } ;
struct ocfs2_extent_block {TYPE_1__ h_list; void* h_suballoc_bit; void* h_suballoc_loc; void* h_suballoc_slot; int /*<<< orphan*/  h_fs_generation; void* h_blkno; int /*<<< orphan*/  h_signature; } ;
struct ocfs2_alloc_context {int /*<<< orphan*/  ac_alloc_slot; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_5__ {int /*<<< orphan*/  s_blocksize; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  OCFS2_EXTENT_BLOCK_SIGNATURE ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_CREATE ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_claim_metadata (int /*<<< orphan*/ *,struct ocfs2_alloc_context*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_extent_recs_per_eb (TYPE_2__*) ; 
 int ocfs2_journal_access_eb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/  ocfs2_metadata_cache_get_super (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_set_new_buffer_uptodate (int /*<<< orphan*/ ,struct buffer_head*) ; 
 struct buffer_head* sb_getblk (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_create_new_meta_bhs(handle_t *handle,
				     struct ocfs2_extent_tree *et,
				     int wanted,
				     struct ocfs2_alloc_context *meta_ac,
				     struct buffer_head *bhs[])
{
	int count, status, i;
	u16 suballoc_bit_start;
	u32 num_got;
	u64 suballoc_loc, first_blkno;
	struct ocfs2_super *osb =
		OCFS2_SB(ocfs2_metadata_cache_get_super(et->et_ci));
	struct ocfs2_extent_block *eb;

	count = 0;
	while (count < wanted) {
		status = ocfs2_claim_metadata(handle,
					      meta_ac,
					      wanted - count,
					      &suballoc_loc,
					      &suballoc_bit_start,
					      &num_got,
					      &first_blkno);
		if (status < 0) {
			mlog_errno(status);
			goto bail;
		}

		for(i = count;  i < (num_got + count); i++) {
			bhs[i] = sb_getblk(osb->sb, first_blkno);
			if (bhs[i] == NULL) {
				status = -ENOMEM;
				mlog_errno(status);
				goto bail;
			}
			ocfs2_set_new_buffer_uptodate(et->et_ci, bhs[i]);

			status = ocfs2_journal_access_eb(handle, et->et_ci,
							 bhs[i],
							 OCFS2_JOURNAL_ACCESS_CREATE);
			if (status < 0) {
				mlog_errno(status);
				goto bail;
			}

			memset(bhs[i]->b_data, 0, osb->sb->s_blocksize);
			eb = (struct ocfs2_extent_block *) bhs[i]->b_data;
			/* Ok, setup the minimal stuff here. */
			strcpy(eb->h_signature, OCFS2_EXTENT_BLOCK_SIGNATURE);
			eb->h_blkno = cpu_to_le64(first_blkno);
			eb->h_fs_generation = cpu_to_le32(osb->fs_generation);
			eb->h_suballoc_slot =
				cpu_to_le16(meta_ac->ac_alloc_slot);
			eb->h_suballoc_loc = cpu_to_le64(suballoc_loc);
			eb->h_suballoc_bit = cpu_to_le16(suballoc_bit_start);
			eb->h_list.l_count =
				cpu_to_le16(ocfs2_extent_recs_per_eb(osb->sb));

			suballoc_bit_start++;
			first_blkno++;

			/* We'll also be dirtied by the caller, so
			 * this isn't absolutely necessary. */
			ocfs2_journal_dirty(handle, bhs[i]);
		}

		count += num_got;
	}

	status = 0;
bail:
	if (status < 0) {
		for(i = 0; i < wanted; i++) {
			brelse(bhs[i]);
			bhs[i] = NULL;
		}
		mlog_errno(status);
	}
	return status;
}