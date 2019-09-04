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

/* Variables and functions */
 scalar_t__ MIN_GREEN ; 
 scalar_t__ MIN_RED ; 
 char* PERF_COLOR_GREEN ; 
 char* PERF_COLOR_NORMAL ; 
 char* PERF_COLOR_RED ; 
 scalar_t__ fabs (double) ; 

const char *get_percent_color(double percent)
{
	const char *color = PERF_COLOR_NORMAL;

	/*
	 * We color high-overhead entries in red, mid-overhead
	 * entries in green - and keep the low overhead places
	 * normal:
	 */
	if (fabs(percent) >= MIN_RED)
		color = PERF_COLOR_RED;
	else {
		if (fabs(percent) > MIN_GREEN)
			color = PERF_COLOR_GREEN;
	}
	return color;
}