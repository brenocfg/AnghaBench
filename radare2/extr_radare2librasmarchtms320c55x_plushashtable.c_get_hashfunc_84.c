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

st32 get_hashfunc_84(st32 arg1, st32 arg2) {
	st32 result; 
	st32 v2 = arg2 & 0x1000180;
	if ( arg2 & 0x1000180 ) {
		if ( v2 == 16777344 ) {
			result = 509;
		} else {
			if (v2 == 16777472) {
				result = 510;
			} else {
				result = arg1;
			}
		}
	} else {
		result = 508;
	}
	return result;
}