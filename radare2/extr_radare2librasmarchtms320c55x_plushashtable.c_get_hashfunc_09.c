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
typedef  int st32 ;

/* Variables and functions */

st32 get_hashfunc_09(st32 arg1, st32 arg2) {
	st32 v2; 

	v2 = arg2 & 0xC0000000;
	if ( (arg2 & 0xC0000000u) <= 0x80000000 ) {
		if ((arg2 & 0xC0000000) == 0x80000000) {
			return 91;
		}
		if (!v2) {
			return 89;
		}
		if (v2 == 0x40000000) {
			return 90;
		}
		return arg1;
	}
	if (v2 != 0xC0000000) {
		return arg1;
	}
	return 92;
}