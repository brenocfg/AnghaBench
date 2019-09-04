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
typedef  int u32 ;
struct arena_info {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int EIO ; 
 int MAP_ENT_NORMAL ; 
 int MAP_ERR_SHIFT ; 
 int MAP_TRIM_SHIFT ; 
 int __btt_map_write (struct arena_info*,int,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*) ; 
 int ent_lba (int) ; 
 int /*<<< orphan*/  to_dev (struct arena_info*) ; 

__attribute__((used)) static int btt_map_write(struct arena_info *arena, u32 lba, u32 mapping,
			u32 z_flag, u32 e_flag, unsigned long rwb_flags)
{
	u32 ze;
	__le32 mapping_le;

	/*
	 * This 'mapping' is supposed to be just the LBA mapping, without
	 * any flags set, so strip the flag bits.
	 */
	mapping = ent_lba(mapping);

	ze = (z_flag << 1) + e_flag;
	switch (ze) {
	case 0:
		/*
		 * We want to set neither of the Z or E flags, and
		 * in the actual layout, this means setting the bit
		 * positions of both to '1' to indicate a 'normal'
		 * map entry
		 */
		mapping |= MAP_ENT_NORMAL;
		break;
	case 1:
		mapping |= (1 << MAP_ERR_SHIFT);
		break;
	case 2:
		mapping |= (1 << MAP_TRIM_SHIFT);
		break;
	default:
		/*
		 * The case where Z and E are both sent in as '1' could be
		 * construed as a valid 'normal' case, but we decide not to,
		 * to avoid confusion
		 */
		dev_err_ratelimited(to_dev(arena),
			"Invalid use of Z and E flags\n");
		return -EIO;
	}

	mapping_le = cpu_to_le32(mapping);
	return __btt_map_write(arena, lba, mapping_le, rwb_flags);
}