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
typedef  unsigned int u32 ;
struct extent_buffer {int dummy; } ;

/* Variables and functions */
 unsigned long BITS_PER_BYTE ; 
 int EINVAL ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  bitmap_clear (unsigned long*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  bitmap_set (unsigned long*,unsigned long,int) ; 
 int check_eb_bitmap (unsigned long*,struct extent_buffer*,unsigned long) ; 
 int /*<<< orphan*/  extent_buffer_bitmap_clear (struct extent_buffer*,unsigned long,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  extent_buffer_bitmap_set (struct extent_buffer*,unsigned long,unsigned long,int) ; 
 scalar_t__ memcmp_extent_buffer (struct extent_buffer*,unsigned long*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  memset (unsigned long*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  memzero_extent_buffer (struct extent_buffer*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  test_err (char*) ; 

__attribute__((used)) static int __test_eb_bitmaps(unsigned long *bitmap, struct extent_buffer *eb,
			     unsigned long len)
{
	unsigned long i, j;
	u32 x;
	int ret;

	memset(bitmap, 0, len);
	memzero_extent_buffer(eb, 0, len);
	if (memcmp_extent_buffer(eb, bitmap, 0, len) != 0) {
		test_err("bitmap was not zeroed");
		return -EINVAL;
	}

	bitmap_set(bitmap, 0, len * BITS_PER_BYTE);
	extent_buffer_bitmap_set(eb, 0, 0, len * BITS_PER_BYTE);
	ret = check_eb_bitmap(bitmap, eb, len);
	if (ret) {
		test_err("setting all bits failed");
		return ret;
	}

	bitmap_clear(bitmap, 0, len * BITS_PER_BYTE);
	extent_buffer_bitmap_clear(eb, 0, 0, len * BITS_PER_BYTE);
	ret = check_eb_bitmap(bitmap, eb, len);
	if (ret) {
		test_err("clearing all bits failed");
		return ret;
	}

	/* Straddling pages test */
	if (len > PAGE_SIZE) {
		bitmap_set(bitmap,
			(PAGE_SIZE - sizeof(long) / 2) * BITS_PER_BYTE,
			sizeof(long) * BITS_PER_BYTE);
		extent_buffer_bitmap_set(eb, PAGE_SIZE - sizeof(long) / 2, 0,
					sizeof(long) * BITS_PER_BYTE);
		ret = check_eb_bitmap(bitmap, eb, len);
		if (ret) {
			test_err("setting straddling pages failed");
			return ret;
		}

		bitmap_set(bitmap, 0, len * BITS_PER_BYTE);
		bitmap_clear(bitmap,
			(PAGE_SIZE - sizeof(long) / 2) * BITS_PER_BYTE,
			sizeof(long) * BITS_PER_BYTE);
		extent_buffer_bitmap_set(eb, 0, 0, len * BITS_PER_BYTE);
		extent_buffer_bitmap_clear(eb, PAGE_SIZE - sizeof(long) / 2, 0,
					sizeof(long) * BITS_PER_BYTE);
		ret = check_eb_bitmap(bitmap, eb, len);
		if (ret) {
			test_err("clearing straddling pages failed");
			return ret;
		}
	}

	/*
	 * Generate a wonky pseudo-random bit pattern for the sake of not using
	 * something repetitive that could miss some hypothetical off-by-n bug.
	 */
	x = 0;
	bitmap_clear(bitmap, 0, len * BITS_PER_BYTE);
	extent_buffer_bitmap_clear(eb, 0, 0, len * BITS_PER_BYTE);
	for (i = 0; i < len * BITS_PER_BYTE / 32; i++) {
		x = (0x19660dULL * (u64)x + 0x3c6ef35fULL) & 0xffffffffU;
		for (j = 0; j < 32; j++) {
			if (x & (1U << j)) {
				bitmap_set(bitmap, i * 32 + j, 1);
				extent_buffer_bitmap_set(eb, 0, i * 32 + j, 1);
			}
		}
	}

	ret = check_eb_bitmap(bitmap, eb, len);
	if (ret) {
		test_err("random bit pattern failed");
		return ret;
	}

	return 0;
}