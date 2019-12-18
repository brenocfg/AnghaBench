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
typedef  int ut8 ;

/* Variables and functions */

const char * get_freg_str(ut8 key, char * str)
{
	static const char * table[16] = {
		"ac0", "ac1", "ac2", "ac3", "t0", "t1", "t2", "t3",
		"ar0", "ar1", "ar2", "ar3", "ar4", "ar5", "ar6", "ar7",
	};

	return table[ key & 15 ];
}