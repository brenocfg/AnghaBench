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

/* Variables and functions */
 int /*<<< orphan*/  __ETHTOOL_LINK_MODE_MASK_NBITS ; 
 int /*<<< orphan*/  bitmap_copy (unsigned long*,unsigned long const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void linkmode_copy(unsigned long *dst, const unsigned long *src)
{
	bitmap_copy(dst, src, __ETHTOOL_LINK_MODE_MASK_NBITS);
}