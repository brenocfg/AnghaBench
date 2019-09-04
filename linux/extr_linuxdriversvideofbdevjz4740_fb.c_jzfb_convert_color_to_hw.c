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
typedef  unsigned int uint32_t ;
struct fb_bitfield {unsigned int length; unsigned int offset; } ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t jzfb_convert_color_to_hw(unsigned val,
	struct fb_bitfield *bf)
{
	return (((val << bf->length) + 0x7FFF - val) >> 16) << bf->offset;
}