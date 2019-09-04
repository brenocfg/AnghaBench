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
 int /*<<< orphan*/  __ETHTOOL_LINK_MODE_MASK_NBITS ; 
 int /*<<< orphan*/  bitmap_zero (unsigned long*,int /*<<< orphan*/ ) ; 

void ethtool_convert_legacy_u32_to_link_mode(unsigned long *dst,
					     u32 legacy_u32)
{
	bitmap_zero(dst, __ETHTOOL_LINK_MODE_MASK_NBITS);
	dst[0] = legacy_u32;
}