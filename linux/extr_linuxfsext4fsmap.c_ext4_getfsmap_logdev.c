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
struct super_block {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  fmr_owner; int /*<<< orphan*/  fmr_length; int /*<<< orphan*/  fmr_physical; } ;
struct ext4_fsmap {scalar_t__ fmr_physical; scalar_t__ fmr_flags; int /*<<< orphan*/  fmr_owner; scalar_t__ fmr_length; } ;
struct ext4_getfsmap_info {TYPE_2__ gfi_high; int /*<<< orphan*/  gfi_dev; struct ext4_fsmap gfi_low; } ;
struct TYPE_4__ {scalar_t__ j_blk_offset; scalar_t__ j_maxlen; } ;
typedef  TYPE_1__ journal_t ;
struct TYPE_6__ {TYPE_1__* s_journal; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_FMR_OWN_LOG ; 
 TYPE_3__* EXT4_SB (struct super_block*) ; 
 int ext4_getfsmap_helper (struct super_block*,struct ext4_getfsmap_info*,struct ext4_fsmap*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  trace_ext4_fsmap_high_key (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ext4_fsmap_low_key (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_getfsmap_logdev(struct super_block *sb, struct ext4_fsmap *keys,
				struct ext4_getfsmap_info *info)
{
	journal_t *journal = EXT4_SB(sb)->s_journal;
	struct ext4_fsmap irec;

	/* Set up search keys */
	info->gfi_low = keys[0];
	info->gfi_low.fmr_length = 0;

	memset(&info->gfi_high, 0xFF, sizeof(info->gfi_high));

	trace_ext4_fsmap_low_key(sb, info->gfi_dev, 0,
			info->gfi_low.fmr_physical,
			info->gfi_low.fmr_length,
			info->gfi_low.fmr_owner);

	trace_ext4_fsmap_high_key(sb, info->gfi_dev, 0,
			info->gfi_high.fmr_physical,
			info->gfi_high.fmr_length,
			info->gfi_high.fmr_owner);

	if (keys[0].fmr_physical > 0)
		return 0;

	/* Fabricate an rmap entry for the external log device. */
	irec.fmr_physical = journal->j_blk_offset;
	irec.fmr_length = journal->j_maxlen;
	irec.fmr_owner = EXT4_FMR_OWN_LOG;
	irec.fmr_flags = 0;

	return ext4_getfsmap_helper(sb, info, &irec);
}