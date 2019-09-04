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
 double MIN_GREEN ; 
 double MIN_RED ; 

const char *perf_gtk__get_percent_color(double percent)
{
	if (percent >= MIN_RED)
		return "<span fgcolor='red'>";
	if (percent >= MIN_GREEN)
		return "<span fgcolor='dark green'>";
	return NULL;
}