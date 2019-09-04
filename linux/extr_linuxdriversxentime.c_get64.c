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
typedef  int u64 ;
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 scalar_t__ READ_ONCE (int const) ; 

__attribute__((used)) static u64 get64(const u64 *p)
{
	u64 ret;

	if (BITS_PER_LONG < 64) {
		u32 *p32 = (u32 *)p;
		u32 h, l, h2;

		/*
		 * Read high then low, and then make sure high is
		 * still the same; this will only loop if low wraps
		 * and carries into high.
		 * XXX some clean way to make this endian-proof?
		 */
		do {
			h = READ_ONCE(p32[1]);
			l = READ_ONCE(p32[0]);
			h2 = READ_ONCE(p32[1]);
		} while(h2 != h);

		ret = (((u64)h) << 32) | l;
	} else
		ret = READ_ONCE(*p);

	return ret;
}