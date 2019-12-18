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
 int hash_const_05 ; 

st32 get_hashfunc_50(st32 arg1, st32 arg2) {
	st32 v3 = arg2 & 0x780000;
	if ( (ut32)v3 <= 0x400000 ) {
		if (v3 == 4194304) {
			return 522;
		}
		if ( (ut32)v3 > 0x180000 ) {
			if (v3 == 2621440) {
				return 402;
			}
			if (v3 == 3145728) {
				return 411;
			}
		} else {
			if (v3 == 1572864) {
				return 401;
			}
			if (!v3) {
				return 403;
			}
			if (v3 == 524288) {
				return 400;
			}
		}
		return arg1;
	}
	if ((ut32)v3 <= 0x680000) {
		if (v3 == 0x680000) {
			return 526;
		}
		if (v3 == hash_const_05) {
			return 524;
		}
		if (v3 == 0x580000) {
			return 525;
		}
		return arg1;
	}
	if (v3 != 7340032) {
		return arg1;
	}
	return 523;
}