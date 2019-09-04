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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  osd_cdb_offset ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  OSD_DEBUG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int) ; 
 int OSD_OFFSET_MAX_BITS ; 
 int /*<<< orphan*/  _LLU (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 

osd_cdb_offset __osd_encode_offset(
	u64 offset, unsigned *padding, int min_shift, int max_shift)
{
	u64 try_offset = -1, mod, align;
	osd_cdb_offset be32_offset;
	int shift;

	*padding = 0;
	if (!offset)
		return 0;

	for (shift = min_shift; shift < max_shift; ++shift) {
		try_offset = offset >> shift;
		if (try_offset < (1 << OSD_OFFSET_MAX_BITS))
			break;
	}

	BUG_ON(shift == max_shift);

	align = 1 << shift;
	mod = offset & (align - 1);
	if (mod) {
		*padding = align - mod;
		try_offset += 1;
	}

	try_offset |= ((shift - 8) & 0xf) << 28;
	be32_offset = cpu_to_be32((u32)try_offset);

	OSD_DEBUG("offset=%llu mantissa=%llu exp=%d encoded=%x pad=%d\n",
		 _LLU(offset), _LLU(try_offset & 0x0FFFFFFF), shift,
		 be32_offset, *padding);
	return be32_offset;
}