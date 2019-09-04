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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  usa_count; int /*<<< orphan*/  magic; int /*<<< orphan*/  usa_ofs; } ;
typedef  TYPE_1__ NTFS_RECORD ;

/* Variables and functions */
 int EINVAL ; 
 int NTFS_BLOCK_SIZE ; 
 int const NTFS_BLOCK_SIZE_BITS ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  magic_BAAD ; 

int post_read_mst_fixup(NTFS_RECORD *b, const u32 size)
{
	u16 usa_ofs, usa_count, usn;
	u16 *usa_pos, *data_pos;

	/* Setup the variables. */
	usa_ofs = le16_to_cpu(b->usa_ofs);
	/* Decrement usa_count to get number of fixups. */
	usa_count = le16_to_cpu(b->usa_count) - 1;
	/* Size and alignment checks. */
	if ( size & (NTFS_BLOCK_SIZE - 1)	||
	     usa_ofs & 1			||
	     usa_ofs + (usa_count * 2) > size	||
	     (size >> NTFS_BLOCK_SIZE_BITS) != usa_count)
		return 0;
	/* Position of usn in update sequence array. */
	usa_pos = (u16*)b + usa_ofs/sizeof(u16);
	/*
	 * The update sequence number which has to be equal to each of the
	 * u16 values before they are fixed up. Note no need to care for
	 * endianness since we are comparing and moving data for on disk
	 * structures which means the data is consistent. - If it is
	 * consistenty the wrong endianness it doesn't make any difference.
	 */
	usn = *usa_pos;
	/*
	 * Position in protected data of first u16 that needs fixing up.
	 */
	data_pos = (u16*)b + NTFS_BLOCK_SIZE/sizeof(u16) - 1;
	/*
	 * Check for incomplete multi sector transfer(s).
	 */
	while (usa_count--) {
		if (*data_pos != usn) {
			/*
			 * Incomplete multi sector transfer detected! )-:
			 * Set the magic to "BAAD" and return failure.
			 * Note that magic_BAAD is already converted to le32.
			 */
			b->magic = magic_BAAD;
			return -EINVAL;
		}
		data_pos += NTFS_BLOCK_SIZE/sizeof(u16);
	}
	/* Re-setup the variables. */
	usa_count = le16_to_cpu(b->usa_count) - 1;
	data_pos = (u16*)b + NTFS_BLOCK_SIZE/sizeof(u16) - 1;
	/* Fixup all sectors. */
	while (usa_count--) {
		/*
		 * Increment position in usa and restore original data from
		 * the usa into the data buffer.
		 */
		*data_pos = *(++usa_pos);
		/* Increment position in data as well. */
		data_pos += NTFS_BLOCK_SIZE/sizeof(u16);
	}
	return 0;
}