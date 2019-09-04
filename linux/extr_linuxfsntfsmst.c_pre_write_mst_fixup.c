#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  le16 ;
struct TYPE_3__ {int /*<<< orphan*/  usa_count; int /*<<< orphan*/  usa_ofs; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ NTFS_RECORD ;

/* Variables and functions */
 int EINVAL ; 
 int NTFS_BLOCK_SIZE ; 
 int const NTFS_BLOCK_SIZE_BITS ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le16_to_cpup (int /*<<< orphan*/ *) ; 
 scalar_t__ ntfs_is_baad_record (int /*<<< orphan*/ ) ; 
 scalar_t__ ntfs_is_hole_record (int /*<<< orphan*/ ) ; 

int pre_write_mst_fixup(NTFS_RECORD *b, const u32 size)
{
	le16 *usa_pos, *data_pos;
	u16 usa_ofs, usa_count, usn;
	le16 le_usn;

	/* Sanity check + only fixup if it makes sense. */
	if (!b || ntfs_is_baad_record(b->magic) ||
			ntfs_is_hole_record(b->magic))
		return -EINVAL;
	/* Setup the variables. */
	usa_ofs = le16_to_cpu(b->usa_ofs);
	/* Decrement usa_count to get number of fixups. */
	usa_count = le16_to_cpu(b->usa_count) - 1;
	/* Size and alignment checks. */
	if ( size & (NTFS_BLOCK_SIZE - 1)	||
	     usa_ofs & 1			||
	     usa_ofs + (usa_count * 2) > size	||
	     (size >> NTFS_BLOCK_SIZE_BITS) != usa_count)
		return -EINVAL;
	/* Position of usn in update sequence array. */
	usa_pos = (le16*)((u8*)b + usa_ofs);
	/*
	 * Cyclically increment the update sequence number
	 * (skipping 0 and -1, i.e. 0xffff).
	 */
	usn = le16_to_cpup(usa_pos) + 1;
	if (usn == 0xffff || !usn)
		usn = 1;
	le_usn = cpu_to_le16(usn);
	*usa_pos = le_usn;
	/* Position in data of first u16 that needs fixing up. */
	data_pos = (le16*)b + NTFS_BLOCK_SIZE/sizeof(le16) - 1;
	/* Fixup all sectors. */
	while (usa_count--) {
		/*
		 * Increment the position in the usa and save the
		 * original data from the data buffer into the usa.
		 */
		*(++usa_pos) = *data_pos;
		/* Apply fixup to data. */
		*data_pos = le_usn;
		/* Increment position in data as well. */
		data_pos += NTFS_BLOCK_SIZE/sizeof(le16);
	}
	return 0;
}