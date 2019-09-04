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
struct seg_entry {unsigned short type; unsigned short valid_blocks; int /*<<< orphan*/  mtime; int /*<<< orphan*/  cur_valid_map; } ;
struct f2fs_sit_entry {int /*<<< orphan*/  mtime; int /*<<< orphan*/  valid_map; int /*<<< orphan*/  vblocks; } ;

/* Variables and functions */
 unsigned short SIT_VBLOCKS_SHIFT ; 
 int /*<<< orphan*/  SIT_VBLOCK_MAP_SIZE ; 
 int /*<<< orphan*/  cpu_to_le16 (unsigned short) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __seg_info_to_raw_sit(struct seg_entry *se,
					struct f2fs_sit_entry *rs)
{
	unsigned short raw_vblocks = (se->type << SIT_VBLOCKS_SHIFT) |
					se->valid_blocks;
	rs->vblocks = cpu_to_le16(raw_vblocks);
	memcpy(rs->valid_map, se->cur_valid_map, SIT_VBLOCK_MAP_SIZE);
	rs->mtime = cpu_to_le64(se->mtime);
}