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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */

__attribute__((used)) static inline u32 *fill16_col(u32 *dst, int rows, u32 m[])
{
	while (rows) {
		*dst++ = m[0];
#if BPL > 2
		*dst++ = m[1];
#endif
#if BPL > 4
		*dst++ = m[2];
		*dst++ = m[3];
#endif
		rows--;
	}
	return dst;
}