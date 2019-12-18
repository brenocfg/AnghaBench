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

st32 get_hashfunc_32(st32 arg1, st32 arg2) {
	st32 v2; 
	st32 v3; 
	st32 result; 

	v2 = arg2;
	v3 = v2 & 0x18000;
	if ( v3 ) {
		if ( v3 == 32768 ) {
			result = 258;
		} else {
			if (v3 == 65536) {
				result = 259;
			} else {
				result = arg1;
			}
		}
	} else {
		result = 261;
	}
	return result;
}