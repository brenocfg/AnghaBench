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
 scalar_t__ hash_const_05 ; 

st32 get_hashfunc_11(st32 arg1, st32 arg2) {
	st32 result; 

	/* */

	if ( (ut32)hash_const_05 & arg2 ) {
		if (((ut32)hash_const_05 & arg2) == 524288) {
			result = 460;
		} else {
			result = arg1;
		}
	} else {
		result = 244;
	}
	return result;
}