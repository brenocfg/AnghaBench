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
 int hash_const_03 ; 

st32 get_hashfunc_29(st32 arg1, st32 arg2) {
	st32 v2; 
	st32 v3; 

	v2 = arg2;
	v3 = v2 & 0x40F800;
	if ( v3 <= (ut32)hash_const_03 ) {
		//if ( (st32 (*)(int, int, int))v3 == (st32 (*)(int, int, int))hash_const_03)
		if (v3 == hash_const_03) {
			return 305;
		}
		if (v3 == 40960) {
			return 306;
		}
		if (v3 == 57344) {
			return 391;
		}
		return arg1;
	}
	if (v3 != 4218880) {
		return arg1;
	}
	return 390;
}