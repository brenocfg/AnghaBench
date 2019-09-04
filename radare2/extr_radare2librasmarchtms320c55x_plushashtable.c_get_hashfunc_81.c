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

st32 get_hashfunc_81(st32 arg1, st32 arg2) {
	st32 result; 
	st32 v2 = arg2 & 0x1000180;
	if ( (arg2 & 0x1000180u) <= 0x1000000 ) {
		if ((arg2 & 0x1000180) == 16777216) {
			return 191;
		}
		if ( (ut32)v2 > 0x100 ) {
			if (v2 == 384) {
				return 200;
			}
		} else {
			if (v2 == 256) {
				return 538;
			}
			if (!v2) {
				return 190;
			}
			if (v2 == 128) {
				return 537;
			}
		}
		return arg1;
	}
	if ( v2 == 16777344 ) {
		result = 194;
	} else {
		if ( v2 == 16777472 ) {
			result = 539;
		} else {
			if (v2 != 16777600) {
				return arg1;
			}
			result = 201;
		}
	}
	return result;
}