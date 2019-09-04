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
typedef  int u8 ;
typedef  int u64 ;
struct tnum {int dummy; } ;

/* Variables and functions */
 struct tnum TNUM (int,int) ; 
 int fls64 (int) ; 
 struct tnum tnum_unknown ; 

struct tnum tnum_range(u64 min, u64 max)
{
	u64 chi = min ^ max, delta;
	u8 bits = fls64(chi);

	/* special case, needed because 1ULL << 64 is undefined */
	if (bits > 63)
		return tnum_unknown;
	/* e.g. if chi = 4, bits = 3, delta = (1<<3) - 1 = 7.
	 * if chi = 0, bits = 0, delta = (1<<0) - 1 = 0, so we return
	 *  constant min (since min == max).
	 */
	delta = (1ULL << bits) - 1;
	return TNUM(min & ~delta, delta);
}