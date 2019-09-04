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
typedef  int u_int ;
typedef  int u32 ;
struct fb_bitfield {int length; int offset; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 convert_bitfield(u_int val, struct fb_bitfield *bf)
{
	u_int mask = (1 << bf->length) - 1;

	return (val >> (16 - bf->length) & mask) << bf->offset;
}