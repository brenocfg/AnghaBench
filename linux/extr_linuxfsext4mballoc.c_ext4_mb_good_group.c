#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ext4_group_info {unsigned int bb_free; unsigned int bb_fragments; int /*<<< orphan*/  bb_largest_free_order; } ;
struct TYPE_5__ {unsigned int fe_len; } ;
struct ext4_allocation_context {int ac_flags; TYPE_1__ ac_g_ex; int /*<<< orphan*/  ac_2order; TYPE_2__* ac_sb; } ;
typedef  int ext4_group_t ;
struct TYPE_6__ {int /*<<< orphan*/  s_blocksize_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EXT4_FLEX_SIZE_DIR_ALLOC_SCHEME ; 
 int /*<<< orphan*/  EXT4_MB_GRP_BBITMAP_CORRUPT (struct ext4_group_info*) ; 
 int /*<<< orphan*/  EXT4_MB_GRP_NEED_INIT (struct ext4_group_info*) ; 
 int EXT4_MB_HINT_DATA ; 
 int /*<<< orphan*/  EXT4_SB (TYPE_2__*) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int ext4_flex_bg_size (int /*<<< orphan*/ ) ; 
 struct ext4_group_info* ext4_get_group_info (TYPE_2__*,int) ; 
 int ext4_mb_init_group (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_mb_good_group(struct ext4_allocation_context *ac,
				ext4_group_t group, int cr)
{
	unsigned free, fragments;
	int flex_size = ext4_flex_bg_size(EXT4_SB(ac->ac_sb));
	struct ext4_group_info *grp = ext4_get_group_info(ac->ac_sb, group);

	BUG_ON(cr < 0 || cr >= 4);

	free = grp->bb_free;
	if (free == 0)
		return 0;
	if (cr <= 2 && free < ac->ac_g_ex.fe_len)
		return 0;

	if (unlikely(EXT4_MB_GRP_BBITMAP_CORRUPT(grp)))
		return 0;

	/* We only do this if the grp has never been initialized */
	if (unlikely(EXT4_MB_GRP_NEED_INIT(grp))) {
		int ret = ext4_mb_init_group(ac->ac_sb, group, GFP_NOFS);
		if (ret)
			return ret;
	}

	fragments = grp->bb_fragments;
	if (fragments == 0)
		return 0;

	switch (cr) {
	case 0:
		BUG_ON(ac->ac_2order == 0);

		/* Avoid using the first bg of a flexgroup for data files */
		if ((ac->ac_flags & EXT4_MB_HINT_DATA) &&
		    (flex_size >= EXT4_FLEX_SIZE_DIR_ALLOC_SCHEME) &&
		    ((group % flex_size) == 0))
			return 0;

		if ((ac->ac_2order > ac->ac_sb->s_blocksize_bits+1) ||
		    (free / fragments) >= ac->ac_g_ex.fe_len)
			return 1;

		if (grp->bb_largest_free_order < ac->ac_2order)
			return 0;

		return 1;
	case 1:
		if ((free / fragments) >= ac->ac_g_ex.fe_len)
			return 1;
		break;
	case 2:
		if (free >= ac->ac_g_ex.fe_len)
			return 1;
		break;
	case 3:
		return 1;
	default:
		BUG();
	}

	return 0;
}