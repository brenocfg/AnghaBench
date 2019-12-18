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
struct timezone {int tz_minuteswest; int tz_dsttime; } ;

/* Variables and functions */
 int settimeofday (int /*<<< orphan*/ ,struct timezone*) ; 

int set_tz(int min, int dst)
{
	struct timezone tz;

	tz.tz_minuteswest = min;
	tz.tz_dsttime = dst;

	return settimeofday(0, &tz);
}