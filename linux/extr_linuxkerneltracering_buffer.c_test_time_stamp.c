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
typedef  int u64 ;

/* Variables and functions */
 int TS_DELTA_TEST ; 

__attribute__((used)) static inline int test_time_stamp(u64 delta)
{
	if (delta & TS_DELTA_TEST)
		return 1;
	return 0;
}