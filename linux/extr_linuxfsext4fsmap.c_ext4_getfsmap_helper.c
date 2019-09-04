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
struct super_block {int dummy; } ;
struct ext4_sb_info {int dummy; } ;
struct ext4_getfsmap_info {scalar_t__ gfi_next_fsblk; int (* gfi_formatter ) (struct ext4_fsmap*,int /*<<< orphan*/ ) ;TYPE_1__* gfi_head; int /*<<< orphan*/  gfi_format_arg; int /*<<< orphan*/  gfi_dev; scalar_t__ gfi_last; } ;
struct ext4_fsmap {scalar_t__ fmr_physical; scalar_t__ fmr_length; void* fmr_flags; int /*<<< orphan*/  fmr_owner; int /*<<< orphan*/  fmr_device; } ;
typedef  int /*<<< orphan*/  ext4_grpblk_t ;
typedef  int /*<<< orphan*/  ext4_group_t ;
typedef  scalar_t__ ext4_fsblk_t ;
struct TYPE_2__ {scalar_t__ fmh_count; scalar_t__ fmh_entries; } ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  EXT4_C2B (struct ext4_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT4_FMR_OWN_UNKNOWN ; 
 int EXT4_QUERY_RANGE_ABORT ; 
 int EXT4_QUERY_RANGE_CONTINUE ; 
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 void* FMR_OF_SPECIAL_OWNER ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  ext4_get_group_no_and_offset (struct super_block*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ext4_getfsmap_rec_before_low_key (struct ext4_getfsmap_info*,struct ext4_fsmap*) ; 
 scalar_t__ fatal_signal_pending (int /*<<< orphan*/ ) ; 
 int stub1 (struct ext4_fsmap*,int /*<<< orphan*/ ) ; 
 int stub2 (struct ext4_fsmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ext4_fsmap_mapping (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_getfsmap_helper(struct super_block *sb,
				struct ext4_getfsmap_info *info,
				struct ext4_fsmap *rec)
{
	struct ext4_fsmap fmr;
	struct ext4_sb_info *sbi = EXT4_SB(sb);
	ext4_fsblk_t rec_fsblk = rec->fmr_physical;
	ext4_group_t agno;
	ext4_grpblk_t cno;
	int error;

	if (fatal_signal_pending(current))
		return -EINTR;

	/*
	 * Filter out records that start before our startpoint, if the
	 * caller requested that.
	 */
	if (ext4_getfsmap_rec_before_low_key(info, rec)) {
		rec_fsblk += rec->fmr_length;
		if (info->gfi_next_fsblk < rec_fsblk)
			info->gfi_next_fsblk = rec_fsblk;
		return EXT4_QUERY_RANGE_CONTINUE;
	}

	/* Are we just counting mappings? */
	if (info->gfi_head->fmh_count == 0) {
		if (rec_fsblk > info->gfi_next_fsblk)
			info->gfi_head->fmh_entries++;

		if (info->gfi_last)
			return EXT4_QUERY_RANGE_CONTINUE;

		info->gfi_head->fmh_entries++;

		rec_fsblk += rec->fmr_length;
		if (info->gfi_next_fsblk < rec_fsblk)
			info->gfi_next_fsblk = rec_fsblk;
		return EXT4_QUERY_RANGE_CONTINUE;
	}

	/*
	 * If the record starts past the last physical block we saw,
	 * then we've found a gap.  Report the gap as being owned by
	 * whatever the caller specified is the missing owner.
	 */
	if (rec_fsblk > info->gfi_next_fsblk) {
		if (info->gfi_head->fmh_entries >= info->gfi_head->fmh_count)
			return EXT4_QUERY_RANGE_ABORT;

		ext4_get_group_no_and_offset(sb, info->gfi_next_fsblk,
				&agno, &cno);
		trace_ext4_fsmap_mapping(sb, info->gfi_dev, agno,
				EXT4_C2B(sbi, cno),
				rec_fsblk - info->gfi_next_fsblk,
				EXT4_FMR_OWN_UNKNOWN);

		fmr.fmr_device = info->gfi_dev;
		fmr.fmr_physical = info->gfi_next_fsblk;
		fmr.fmr_owner = EXT4_FMR_OWN_UNKNOWN;
		fmr.fmr_length = rec_fsblk - info->gfi_next_fsblk;
		fmr.fmr_flags = FMR_OF_SPECIAL_OWNER;
		error = info->gfi_formatter(&fmr, info->gfi_format_arg);
		if (error)
			return error;
		info->gfi_head->fmh_entries++;
	}

	if (info->gfi_last)
		goto out;

	/* Fill out the extent we found */
	if (info->gfi_head->fmh_entries >= info->gfi_head->fmh_count)
		return EXT4_QUERY_RANGE_ABORT;

	ext4_get_group_no_and_offset(sb, rec_fsblk, &agno, &cno);
	trace_ext4_fsmap_mapping(sb, info->gfi_dev, agno, EXT4_C2B(sbi, cno),
			rec->fmr_length, rec->fmr_owner);

	fmr.fmr_device = info->gfi_dev;
	fmr.fmr_physical = rec_fsblk;
	fmr.fmr_owner = rec->fmr_owner;
	fmr.fmr_flags = FMR_OF_SPECIAL_OWNER;
	fmr.fmr_length = rec->fmr_length;
	error = info->gfi_formatter(&fmr, info->gfi_format_arg);
	if (error)
		return error;
	info->gfi_head->fmh_entries++;

out:
	rec_fsblk += rec->fmr_length;
	if (info->gfi_next_fsblk < rec_fsblk)
		info->gfi_next_fsblk = rec_fsblk;
	return EXT4_QUERY_RANGE_CONTINUE;
}