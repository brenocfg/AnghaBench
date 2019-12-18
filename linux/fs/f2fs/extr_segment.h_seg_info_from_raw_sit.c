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
struct seg_entry {int /*<<< orphan*/  mtime; int /*<<< orphan*/  type; int /*<<< orphan*/  cur_valid_map_mir; int /*<<< orphan*/  ckpt_valid_map; int /*<<< orphan*/  cur_valid_map; void* ckpt_valid_blocks; void* valid_blocks; } ;
struct f2fs_sit_entry {int /*<<< orphan*/  mtime; int /*<<< orphan*/  valid_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_SIT_TYPE (struct f2fs_sit_entry*) ; 
 void* GET_SIT_VBLOCKS (struct f2fs_sit_entry*) ; 
 int /*<<< orphan*/  SIT_VBLOCK_MAP_SIZE ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void seg_info_from_raw_sit(struct seg_entry *se,
					struct f2fs_sit_entry *rs)
{
	se->valid_blocks = GET_SIT_VBLOCKS(rs);
	se->ckpt_valid_blocks = GET_SIT_VBLOCKS(rs);
	memcpy(se->cur_valid_map, rs->valid_map, SIT_VBLOCK_MAP_SIZE);
	memcpy(se->ckpt_valid_map, rs->valid_map, SIT_VBLOCK_MAP_SIZE);
#ifdef CONFIG_F2FS_CHECK_FS
	memcpy(se->cur_valid_map_mir, rs->valid_map, SIT_VBLOCK_MAP_SIZE);
#endif
	se->type = GET_SIT_TYPE(rs);
	se->mtime = le64_to_cpu(rs->mtime);
}