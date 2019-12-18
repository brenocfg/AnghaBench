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

st32 get_hashfunc_24(st32 arg1, st32 arg2) {
	st32 v2; 
	st32 v3; 

	v2 = arg2;
	v3 = v2 & 0x418000;
	if ( (ut32)v3 <= 0x400000 ) {
		if (v3 == 4194304) {
			return 330;
		}
		if ( (ut32)v3 <= 0x10000 ) {
			if ( v3 != 65536 ) {
				if (!v3) {
					return 329;
				}
				if (v3 == 32768) {
					return 307;
				}
				return arg1;
			}
			return 480;
		}
		if (v3 == 98304) {
			return 467;
		}
		return arg1;
	}
	//if ( (st32 (*)(char))v3 != (char *)hash_const_01 ) {
	if (v3 != hash_const_01) {
		if (v3 == 4259840) {
			return 480;
		}
		if (v3 == 4292608) {
			return 467;
		}
		return arg1;
	}
	return 308;
}