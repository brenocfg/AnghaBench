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

__attribute__((used)) static bool is_aligned(const void *base, size_t size, unsigned char align)
{
	unsigned char lsbits = (unsigned char)size;

	(void)base;
#ifndef CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
	lsbits |= (unsigned char)(uintptr_t)base;
#endif
	return (lsbits & (align - 1)) == 0;
}