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
typedef  size_t u8 ;

/* Variables and functions */
 int /*<<< orphan*/  ktime_get_real_seconds () ; 
 int /*<<< orphan*/ * tomoyo_stat_modified ; 
 int /*<<< orphan*/ * tomoyo_stat_updated ; 

void tomoyo_update_stat(const u8 index)
{
	/*
	 * I don't use atomic operations because race condition is not fatal.
	 */
	tomoyo_stat_updated[index]++;
	tomoyo_stat_modified[index] = ktime_get_real_seconds();
}