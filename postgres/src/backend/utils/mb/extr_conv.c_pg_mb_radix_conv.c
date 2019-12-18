#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32 ;
typedef  size_t uint16 ;
struct TYPE_3__ {unsigned char b4_1_lower; unsigned char b4_1_upper; unsigned char b4_2_lower; unsigned char b4_2_upper; unsigned char b4_3_lower; unsigned char b4_3_upper; unsigned char b4_4_lower; unsigned char b4_4_upper; size_t* chars32; size_t b4root; size_t* chars16; unsigned char b3_1_lower; unsigned char b3_1_upper; unsigned char b3_2_lower; unsigned char b3_2_upper; unsigned char b3_3_lower; unsigned char b3_3_upper; size_t b3root; unsigned char b2_1_lower; unsigned char b2_1_upper; unsigned char b2_2_lower; unsigned char b2_2_upper; size_t b2root; unsigned char b1_lower; unsigned char b1_upper; unsigned char b1root; } ;
typedef  TYPE_1__ pg_mb_radix_tree ;

/* Variables and functions */

__attribute__((used)) static inline uint32
pg_mb_radix_conv(const pg_mb_radix_tree *rt,
				 int l,
				 unsigned char b1,
				 unsigned char b2,
				 unsigned char b3,
				 unsigned char b4)
{
	if (l == 4)
	{
		/* 4-byte code */

		/* check code validity */
		if (b1 < rt->b4_1_lower || b1 > rt->b4_1_upper ||
			b2 < rt->b4_2_lower || b2 > rt->b4_2_upper ||
			b3 < rt->b4_3_lower || b3 > rt->b4_3_upper ||
			b4 < rt->b4_4_lower || b4 > rt->b4_4_upper)
			return 0;

		/* perform lookup */
		if (rt->chars32)
		{
			uint32		idx = rt->b4root;

			idx = rt->chars32[b1 + idx - rt->b4_1_lower];
			idx = rt->chars32[b2 + idx - rt->b4_2_lower];
			idx = rt->chars32[b3 + idx - rt->b4_3_lower];
			return rt->chars32[b4 + idx - rt->b4_4_lower];
		}
		else
		{
			uint16		idx = rt->b4root;

			idx = rt->chars16[b1 + idx - rt->b4_1_lower];
			idx = rt->chars16[b2 + idx - rt->b4_2_lower];
			idx = rt->chars16[b3 + idx - rt->b4_3_lower];
			return rt->chars16[b4 + idx - rt->b4_4_lower];
		}
	}
	else if (l == 3)
	{
		/* 3-byte code */

		/* check code validity */
		if (b2 < rt->b3_1_lower || b2 > rt->b3_1_upper ||
			b3 < rt->b3_2_lower || b3 > rt->b3_2_upper ||
			b4 < rt->b3_3_lower || b4 > rt->b3_3_upper)
			return 0;

		/* perform lookup */
		if (rt->chars32)
		{
			uint32		idx = rt->b3root;

			idx = rt->chars32[b2 + idx - rt->b3_1_lower];
			idx = rt->chars32[b3 + idx - rt->b3_2_lower];
			return rt->chars32[b4 + idx - rt->b3_3_lower];
		}
		else
		{
			uint16		idx = rt->b3root;

			idx = rt->chars16[b2 + idx - rt->b3_1_lower];
			idx = rt->chars16[b3 + idx - rt->b3_2_lower];
			return rt->chars16[b4 + idx - rt->b3_3_lower];
		}
	}
	else if (l == 2)
	{
		/* 2-byte code */

		/* check code validity - first byte */
		if (b3 < rt->b2_1_lower || b3 > rt->b2_1_upper ||
			b4 < rt->b2_2_lower || b4 > rt->b2_2_upper)
			return 0;

		/* perform lookup */
		if (rt->chars32)
		{
			uint32		idx = rt->b2root;

			idx = rt->chars32[b3 + idx - rt->b2_1_lower];
			return rt->chars32[b4 + idx - rt->b2_2_lower];
		}
		else
		{
			uint16		idx = rt->b2root;

			idx = rt->chars16[b3 + idx - rt->b2_1_lower];
			return rt->chars16[b4 + idx - rt->b2_2_lower];
		}
	}
	else if (l == 1)
	{
		/* 1-byte code */

		/* check code validity - first byte */
		if (b4 < rt->b1_lower || b4 > rt->b1_upper)
			return 0;

		/* perform lookup */
		if (rt->chars32)
			return rt->chars32[b4 + rt->b1root - rt->b1_lower];
		else
			return rt->chars16[b4 + rt->b1root - rt->b1_lower];
	}
	return 0;					/* shouldn't happen */
}