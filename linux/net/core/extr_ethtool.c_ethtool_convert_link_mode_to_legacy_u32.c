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
typedef  unsigned long u32 ;

/* Variables and functions */
 int /*<<< orphan*/  __ETHTOOL_DECLARE_LINK_MODE_MASK (int /*<<< orphan*/ ) ; 
 int __ETHTOOL_LINK_MODE_MASK_NBITS ; 
 int /*<<< orphan*/  bitmap_complement (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bitmap_fill (int /*<<< orphan*/ ,int) ; 
 scalar_t__ bitmap_intersects (int /*<<< orphan*/ ,unsigned long const*,int) ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ext ; 

bool ethtool_convert_link_mode_to_legacy_u32(u32 *legacy_u32,
					     const unsigned long *src)
{
	bool retval = true;

	/* TODO: following test will soon always be true */
	if (__ETHTOOL_LINK_MODE_MASK_NBITS > 32) {
		__ETHTOOL_DECLARE_LINK_MODE_MASK(ext);

		bitmap_zero(ext, __ETHTOOL_LINK_MODE_MASK_NBITS);
		bitmap_fill(ext, 32);
		bitmap_complement(ext, ext, __ETHTOOL_LINK_MODE_MASK_NBITS);
		if (bitmap_intersects(ext, src,
				      __ETHTOOL_LINK_MODE_MASK_NBITS)) {
			/* src mask goes beyond bit 31 */
			retval = false;
		}
	}
	*legacy_u32 = src[0];
	return retval;
}