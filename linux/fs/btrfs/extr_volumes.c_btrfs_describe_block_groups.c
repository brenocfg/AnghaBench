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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_2__ {char* raid_name; int /*<<< orphan*/  bg_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_AVAIL_ALLOC_BIT_SINGLE ; 
 int /*<<< orphan*/  BTRFS_BLOCK_GROUP_DATA ; 
 int /*<<< orphan*/  BTRFS_BLOCK_GROUP_METADATA ; 
 int /*<<< orphan*/  BTRFS_BLOCK_GROUP_SYSTEM ; 
 int BTRFS_NR_RAID_TYPES ; 
 int /*<<< orphan*/  DESCRIBE_FLAG (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* btrfs_raid_array ; 
 int snprintf (char*,scalar_t__,char*,scalar_t__) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

void btrfs_describe_block_groups(u64 bg_flags, char *buf, u32 size_buf)
{
	int i;
	int ret;
	char *bp = buf;
	u64 flags = bg_flags;
	u32 size_bp = size_buf;

	if (!flags) {
		strcpy(bp, "NONE");
		return;
	}

#define DESCRIBE_FLAG(flag, desc)						\
	do {								\
		if (flags & (flag)) {					\
			ret = snprintf(bp, size_bp, "%s|", (desc));	\
			if (ret < 0 || ret >= size_bp)			\
				goto out_overflow;			\
			size_bp -= ret;					\
			bp += ret;					\
			flags &= ~(flag);				\
		}							\
	} while (0)

	DESCRIBE_FLAG(BTRFS_BLOCK_GROUP_DATA, "data");
	DESCRIBE_FLAG(BTRFS_BLOCK_GROUP_SYSTEM, "system");
	DESCRIBE_FLAG(BTRFS_BLOCK_GROUP_METADATA, "metadata");

	DESCRIBE_FLAG(BTRFS_AVAIL_ALLOC_BIT_SINGLE, "single");
	for (i = 0; i < BTRFS_NR_RAID_TYPES; i++)
		DESCRIBE_FLAG(btrfs_raid_array[i].bg_flag,
			      btrfs_raid_array[i].raid_name);
#undef DESCRIBE_FLAG

	if (flags) {
		ret = snprintf(bp, size_bp, "0x%llx|", flags);
		size_bp -= ret;
	}

	if (size_bp < size_buf)
		buf[size_buf - size_bp - 1] = '\0'; /* remove last | */

	/*
	 * The text is trimmed, it's up to the caller to provide sufficiently
	 * large buffer
	 */
out_overflow:;
}