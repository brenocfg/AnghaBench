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
 int hash_const_01 ; 
 scalar_t__ hash_const_02 ; 

st32 get_hashfunc_25(st32 arg1, st32 arg2) {
	ut32 v2; 

	v2 = (ut32)hash_const_02 & arg2;
	if ( ((ut32)hash_const_02 & arg2) <= 0x8000 ) {
		if ( ((ut32)hash_const_02 & arg2) != 32768 ) {
			if ( v2 <= 0x400 ) {
				if ( v2 != 1024 && v2 ) {
					if (v2 == 512) {
						return 365;
					}
					return arg1;
				}
				return 365;
			}
			if (v2 == 1536) {
				return 365;
			}
			return arg1;
		}
		return 382;
	}
	if ( v2 <= 0x8600 ) {
		if (v2 != 34304 && v2 != 33280 && v2 != 33792) {
			return arg1;
		}
		return 382;
	}
	//if ( (st32 (*)(char))v2 != (char *)hash_const_01 )
	if (v2 != hash_const_01) {
		return arg1;
	}
	return 380;
}