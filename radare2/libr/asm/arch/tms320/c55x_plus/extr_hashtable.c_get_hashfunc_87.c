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
typedef  int st32 ;

/* Variables and functions */

st32 get_hashfunc_87(st32 arg1, st32 v2) {
	st32 result; 
	st32 v3 = v2 & 0x79B981;
	if (v3 == 33024 || v3 == 4227328) {
		result = 490;
	} else {
		result = (v3 == 4260097) ? 491 : arg1;
	}
	return result;
}