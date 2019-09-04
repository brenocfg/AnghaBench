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
struct f2fs_sb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  F2FS_DIRTY_DENTS ; 
 int /*<<< orphan*/  F2FS_DIRTY_IMETA ; 
 int /*<<< orphan*/  F2FS_DIRTY_NODES ; 
 int /*<<< orphan*/  SBI_POR_DOING ; 
 scalar_t__ free_sections (struct f2fs_sb_info*) ; 
 int get_blocktype_secs (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ has_curseg_enough_space (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  is_sbi_flag_set (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ reserved_sections (struct f2fs_sb_info*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool has_not_enough_free_secs(struct f2fs_sb_info *sbi,
					int freed, int needed)
{
	int node_secs = get_blocktype_secs(sbi, F2FS_DIRTY_NODES);
	int dent_secs = get_blocktype_secs(sbi, F2FS_DIRTY_DENTS);
	int imeta_secs = get_blocktype_secs(sbi, F2FS_DIRTY_IMETA);

	if (unlikely(is_sbi_flag_set(sbi, SBI_POR_DOING)))
		return false;

	if (free_sections(sbi) + freed == reserved_sections(sbi) + needed &&
			has_curseg_enough_space(sbi))
		return false;
	return (free_sections(sbi) + freed) <=
		(node_secs + 2 * dent_secs + imeta_secs +
		reserved_sections(sbi) + needed);
}