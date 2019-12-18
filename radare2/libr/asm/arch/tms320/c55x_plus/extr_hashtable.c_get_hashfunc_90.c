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

st32 get_hashfunc_90(st32 arg1, st32 arg2) {
	st32 v2; 
	st32 v4; 
	st32 v5; 

	v2 = arg2 & 0x1F901B9;
	if ( (arg2 & 0x1F901B9u) <= 0x1810101 ) {
		if ((arg2 & 0x1F901B9) == 25231617) {
			return 498;
		}
		if ( (ut32)v2 <= 0x1000180 ) {
			if ( v2 != 16777600 ) {
				if (v2 == 8454401) {
					return 497;
				}
				if (v2 == 8454529) {
					return 499;
				}
				return arg1;
			}
			return 489;
		}
		if (v2 == 20971904) {
			return 489;
		}
		return arg1;
	}
	v4 = v2 - 25231744;
	if ( v4 ) {
		v5 = v4 - 1;
		if (!v5) {
			return 500;
		}

		/* FIX */
		v5 -= 0x3FFFFF;
		if(v5 != 0) {
			return arg1;
		}
		/*
		   if ( (_UNKNOWN *)v5 != &unk_3FFFFF )
		   return arg1;
		 */
	}
	return 496;
}