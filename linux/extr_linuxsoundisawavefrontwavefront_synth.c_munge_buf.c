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

__attribute__((used)) static 
unsigned char *
munge_buf (unsigned char *src, unsigned char *dst, unsigned int dst_size)

{
	unsigned int i;
	unsigned int last = dst_size / 2;

	for (i = 0; i < last; i++) {
		*dst++ = src[i] & 0x7f;
		*dst++ = src[i] >> 7;
	}
	return dst;
}