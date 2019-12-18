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

st32 get_hashfunc_53(st32 arg1, st32 arg2) {
	st32 v2 = arg2 & 0x8200;
	st32 result; 

	if (arg2 & 0x8200) {
		if (v2 == 512) {
			result = 530;
		} else {
			result = (v2==0x8000)? 297: arg1;
		}
	} else {
		result = 355;
	}
	return result;
}