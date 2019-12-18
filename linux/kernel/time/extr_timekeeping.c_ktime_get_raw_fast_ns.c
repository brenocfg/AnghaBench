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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  __ktime_get_fast_ns (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tk_fast_raw ; 

u64 ktime_get_raw_fast_ns(void)
{
	return __ktime_get_fast_ns(&tk_fast_raw);
}