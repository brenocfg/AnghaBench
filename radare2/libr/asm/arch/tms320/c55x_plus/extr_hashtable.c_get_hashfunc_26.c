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

st32 get_hashfunc_26(st32 arg1, st32 arg2) {
	st32 v2; 
	st32 v3; 

	v2 = arg2;
	v3 = v2 & 0x41C000;
	if ( (ut32)v3 <= 0x404000 ) {
		if (v3 == 4210688 || v3 == 16384) {
			return 310;
		}
		if ( v3 != 49152 ) {
			if (v3 == 4194304) {
				return 312;
			}
			return arg1;
		}
		return 311;
	}
	//if ( (st32 (*)(char))v3 != (st32 (*)(char))hash_const_01 ) {
	if (v3 != hash_const_01) {
		if (v3 != 4243456) {
			return arg1;
		}
		return 311;
	}
	return 313;
}