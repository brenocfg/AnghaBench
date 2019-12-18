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

st32 get_hashfunc_82(st32 arg1, st32 arg2) {
	st32 v2; 
	st32 result; 

	v2 = arg2 & 0x1000180;
	if ( (arg2 & 0x1000180u) <= 0x100 ) {
		if ((arg2 & 0x1000180) == 256) {
			return 203;
		}
		if (!v2) {
			return 192;
		}
		if (v2 == 128) {
			return 195;
		}
		return arg1;
	}
	if ( v2 == 384 ) {
		result = 198;
	} else {
		if (v2 != 16777600) {
			return arg1;
		}
		result = 196;
	}
	return result;
}