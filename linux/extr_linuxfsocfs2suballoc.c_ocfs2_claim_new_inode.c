#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct ocfs2_suballoc_result {int sr_bits; int /*<<< orphan*/  sr_blkno; int /*<<< orphan*/  sr_bit_offset; int /*<<< orphan*/  sr_bg_blkno; } ;
struct ocfs2_alloc_context {scalar_t__ ac_bits_given; int ac_bits_wanted; scalar_t__ ac_which; TYPE_2__* ac_inode; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_4__ {int /*<<< orphan*/  bg_allocs; } ;
struct TYPE_6__ {TYPE_1__ alloc_stats; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ OCFS2_AC_USE_INODE ; 
 TYPE_3__* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_claim_suballoc_bits (struct ocfs2_alloc_context*,int /*<<< orphan*/ *,int,int,struct ocfs2_suballoc_result*) ; 
 int /*<<< orphan*/  ocfs2_init_inode_ac_group (struct inode*,struct buffer_head*,struct ocfs2_alloc_context*) ; 
 int /*<<< orphan*/  ocfs2_save_inode_ac_group (struct inode*,struct ocfs2_alloc_context*) ; 

int ocfs2_claim_new_inode(handle_t *handle,
			  struct inode *dir,
			  struct buffer_head *parent_fe_bh,
			  struct ocfs2_alloc_context *ac,
			  u64 *suballoc_loc,
			  u16 *suballoc_bit,
			  u64 *fe_blkno)
{
	int status;
	struct ocfs2_suballoc_result res;

	BUG_ON(!ac);
	BUG_ON(ac->ac_bits_given != 0);
	BUG_ON(ac->ac_bits_wanted != 1);
	BUG_ON(ac->ac_which != OCFS2_AC_USE_INODE);

	ocfs2_init_inode_ac_group(dir, parent_fe_bh, ac);

	status = ocfs2_claim_suballoc_bits(ac,
					   handle,
					   1,
					   1,
					   &res);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}
	atomic_inc(&OCFS2_SB(ac->ac_inode->i_sb)->alloc_stats.bg_allocs);

	BUG_ON(res.sr_bits != 1);

	*suballoc_loc = res.sr_bg_blkno;
	*suballoc_bit = res.sr_bit_offset;
	*fe_blkno = res.sr_blkno;
	ac->ac_bits_given++;
	ocfs2_save_inode_ac_group(dir, ac);
	status = 0;
bail:
	if (status)
		mlog_errno(status);
	return status;
}