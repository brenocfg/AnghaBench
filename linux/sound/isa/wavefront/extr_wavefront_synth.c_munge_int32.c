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

__attribute__((used)) static unsigned char *
munge_int32 (unsigned int src,
	     unsigned char *dst,
	     unsigned int dst_size)
{
	unsigned int i;

	for (i = 0; i < dst_size; i++) {
		*dst = src & 0x7F;  /* Mask high bit of LSB */
		src = src >> 7;     /* Rotate Right 7 bits  */
	                            /* Note: we leave the upper bits in place */ 

		dst++;
	}
	return dst;
}