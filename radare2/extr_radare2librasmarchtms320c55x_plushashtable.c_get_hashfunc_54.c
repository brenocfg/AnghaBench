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

st32 get_hashfunc_54(st32 arg1, st32 arg2) {
	st32 v2 = arg2 & 0x8200;
	if ( (ut32)v2 <= 0x8000 ) {
		if (v2 == 32768) {
			return 316;
		}
		if (!(arg2 & 0x8200)) {
			return 410;
		}
		if (v2 == 512) {
			return 531;
		}
		return arg1;
	}
	if (v2 != 33280) {
		return arg1;
	}
	return 315;
}