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
struct ufs_sb_private_info {scalar_t__ s_sbbase; int s_ipg; scalar_t__ s_fpb; int /*<<< orphan*/  s_inopb; } ;
struct TYPE_4__ {int /*<<< orphan*/  cg_initediblk; } ;
struct TYPE_5__ {TYPE_1__ cg_u2; } ;
struct ufs_cylinder_group {TYPE_2__ cg_u; } ;
struct ufs_cg_private_info {int c_cgx; } ;
struct super_block {int s_flags; int /*<<< orphan*/  s_blocksize; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_6__ {struct ufs_sb_private_info* s_uspi; } ;

/* Variables and functions */
 int SB_SYNCHRONOUS ; 
 int /*<<< orphan*/  UCPI_UBH (struct ufs_cg_private_info*) ; 
 int /*<<< orphan*/  UFSD (char*,...) ; 
 TYPE_3__* UFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  fs32_add (struct super_block*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ fs32_to_cpu (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct buffer_head* sb_getblk (struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  sync_dirty_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  ubh_mark_buffer_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubh_sync_block (int /*<<< orphan*/ ) ; 
 scalar_t__ ufs_inotofsba (scalar_t__) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

__attribute__((used)) static void ufs2_init_inodes_chunk(struct super_block *sb,
				   struct ufs_cg_private_info *ucpi,
				   struct ufs_cylinder_group *ucg)
{
	struct buffer_head *bh;
	struct ufs_sb_private_info *uspi = UFS_SB(sb)->s_uspi;
	sector_t beg = uspi->s_sbbase +
		ufs_inotofsba(ucpi->c_cgx * uspi->s_ipg +
			      fs32_to_cpu(sb, ucg->cg_u.cg_u2.cg_initediblk));
	sector_t end = beg + uspi->s_fpb;

	UFSD("ENTER cgno %d\n", ucpi->c_cgx);

	for (; beg < end; ++beg) {
		bh = sb_getblk(sb, beg);
		lock_buffer(bh);
		memset(bh->b_data, 0, sb->s_blocksize);
		set_buffer_uptodate(bh);
		mark_buffer_dirty(bh);
		unlock_buffer(bh);
		if (sb->s_flags & SB_SYNCHRONOUS)
			sync_dirty_buffer(bh);
		brelse(bh);
	}

	fs32_add(sb, &ucg->cg_u.cg_u2.cg_initediblk, uspi->s_inopb);
	ubh_mark_buffer_dirty(UCPI_UBH(ucpi));
	if (sb->s_flags & SB_SYNCHRONOUS)
		ubh_sync_block(UCPI_UBH(ucpi));

	UFSD("EXIT\n");
}