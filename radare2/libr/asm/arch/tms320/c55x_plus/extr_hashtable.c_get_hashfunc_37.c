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

st32 get_hashfunc_37(st32 arg1, st32 arg2) {
	st32 result; 

	if ( (arg2 & 0x1800000) == 8388608 ) {
		result = 473;
	} else {
		if ((arg2 & 0x1800000) == 25165824) {
			result = 474;
		} else {
			result = arg1;
		}
	}
	return result;
}