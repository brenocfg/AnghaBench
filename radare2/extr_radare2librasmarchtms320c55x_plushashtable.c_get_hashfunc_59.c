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
typedef  int ut32 ;
typedef  int st32 ;

/* Variables and functions */

st32 get_hashfunc_59(st32 arg1, st32 arg2) {
	st32 result; 
	st32 v2 = arg2 & 0x8180;
	if ( (ut32)v2 <= 0x100 ) {
		if (v2 == 256) {
			return 505;
		}
		if (!(arg2 & 0x8180)) {
			return 503;
		}
		if (v2 == 128) {
			return 504;
		}
		return arg1;
	}
	if ( v2 == 384 ) {
		result = 506;
	} else {
		if (v2 != 32768) {
			return arg1;
		}
		result = 507;
	}
	return result;
}