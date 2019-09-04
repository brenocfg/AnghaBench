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
struct TYPE_5__ {int nsumblk; scalar_t__ sumbytes; } ;
struct nilfs_segment_buffer {TYPE_2__ sb_sum; } ;
struct TYPE_6__ {scalar_t__ offset; } ;
struct nilfs_sc_info {scalar_t__ sc_blk_cnt; scalar_t__ sc_datablk_cnt; TYPE_3__ sc_binfo_ptr; TYPE_3__ sc_finfo_ptr; TYPE_1__* sc_super; struct nilfs_segment_buffer* sc_curseg; scalar_t__ sc_cno; } ;
struct nilfs_inode_info {scalar_t__ i_cno; int /*<<< orphan*/  i_state; } ;
struct nilfs_finfo {void* fi_cno; void* fi_ndatablk; void* fi_nblocks; void* fi_ino; } ;
struct inode {scalar_t__ i_ino; } ;
typedef  scalar_t__ __u64 ;
struct TYPE_4__ {int s_blocksize; } ;

/* Variables and functions */
 struct nilfs_inode_info* NILFS_I (struct inode*) ; 
 int /*<<< orphan*/  NILFS_I_GCINODE ; 
 scalar_t__ NILFS_ROOT_METADATA_FILE (scalar_t__) ; 
 void* cpu_to_le32 (scalar_t__) ; 
 void* cpu_to_le64 (scalar_t__) ; 
 struct nilfs_finfo* nilfs_segctor_map_segsum_entry (struct nilfs_sc_info*,TYPE_3__*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nilfs_segctor_end_finfo(struct nilfs_sc_info *sci,
				    struct inode *inode)
{
	struct nilfs_finfo *finfo;
	struct nilfs_inode_info *ii;
	struct nilfs_segment_buffer *segbuf;
	__u64 cno;

	if (sci->sc_blk_cnt == 0)
		return;

	ii = NILFS_I(inode);

	if (test_bit(NILFS_I_GCINODE, &ii->i_state))
		cno = ii->i_cno;
	else if (NILFS_ROOT_METADATA_FILE(inode->i_ino))
		cno = 0;
	else
		cno = sci->sc_cno;

	finfo = nilfs_segctor_map_segsum_entry(sci, &sci->sc_finfo_ptr,
						 sizeof(*finfo));
	finfo->fi_ino = cpu_to_le64(inode->i_ino);
	finfo->fi_nblocks = cpu_to_le32(sci->sc_blk_cnt);
	finfo->fi_ndatablk = cpu_to_le32(sci->sc_datablk_cnt);
	finfo->fi_cno = cpu_to_le64(cno);

	segbuf = sci->sc_curseg;
	segbuf->sb_sum.sumbytes = sci->sc_binfo_ptr.offset +
		sci->sc_super->s_blocksize * (segbuf->sb_sum.nsumblk - 1);
	sci->sc_finfo_ptr = sci->sc_binfo_ptr;
	sci->sc_blk_cnt = sci->sc_datablk_cnt = 0;
}