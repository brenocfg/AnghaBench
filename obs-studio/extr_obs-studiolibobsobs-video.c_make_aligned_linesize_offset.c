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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t make_aligned_linesize_offset(uint32_t offset,
		uint32_t dst_linesize, uint32_t src_linesize)
{
	uint32_t remainder = offset % dst_linesize;
	return (offset / dst_linesize) * src_linesize + remainder;
}