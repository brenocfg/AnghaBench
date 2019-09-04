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

st32 get_hashfunc_79(st32 arg1, st32 arg2) {
	st32 v2; 
	st32 v3; 
	st32 result; 

	v2 = arg2;
	v3 = v2 & 0x18180;
	if ( (ut32)v3 <= 0x8100 ) {
		if (v3 == 33024) {
			return 437;
		}
		if ( (ut32)v3 > 0x180 ) {
			if (v3 == 32768) {
				return 431;
			}
			if (v3 == 32896) {
				return 435;
			}
		} else {
			if (v3 == 384) {
				return 440;
			}
			if (!v3) {
				return 430;
			}
			if (v3 == 128) {
				return 432;
			}
			if (v3 == 256) {
				return 434;
			}
		}
		return arg1;
	}
	if ( (ut32)v3 <= 0x10100 ) {
		if (v3 == 65792) {
			return 442;
		}
		if (v3 == 33152) {
			return 441;
		}
		if (v3 == 65536) {
			return 433;
		}
		if (v3 == 65664) {
			return 436;
		}
		return arg1;
	}
	if ( v3 == 65920 ) {
		result = 439;
	} else {
		if (v3 != 98688) {
			return arg1;
		}
		result = 438;
	}
	return result;
}