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
 char* _ (char*) ; 
 double floor (double) ; 
 int /*<<< orphan*/  printf (char*,double,...) ; 

__attribute__((used)) static void
PrintTiming(double elapsed_msec)
{
	double		seconds;
	double		minutes;
	double		hours;
	double		days;

	if (elapsed_msec < 1000.0)
	{
		/* This is the traditional (pre-v10) output format */
		printf(_("Time: %.3f ms\n"), elapsed_msec);
		return;
	}

	/*
	 * Note: we could print just seconds, in a format like %06.3f, when the
	 * total is less than 1min.  But that's hard to interpret unless we tack
	 * on "s" or otherwise annotate it.  Forcing the display to include
	 * minutes seems like a better solution.
	 */
	seconds = elapsed_msec / 1000.0;
	minutes = floor(seconds / 60.0);
	seconds -= 60.0 * minutes;
	if (minutes < 60.0)
	{
		printf(_("Time: %.3f ms (%02d:%06.3f)\n"),
			   elapsed_msec, (int) minutes, seconds);
		return;
	}

	hours = floor(minutes / 60.0);
	minutes -= 60.0 * hours;
	if (hours < 24.0)
	{
		printf(_("Time: %.3f ms (%02d:%02d:%06.3f)\n"),
			   elapsed_msec, (int) hours, (int) minutes, seconds);
		return;
	}

	days = floor(hours / 24.0);
	hours -= 24.0 * days;
	printf(_("Time: %.3f ms (%.0f d %02d:%02d:%06.3f)\n"),
		   elapsed_msec, days, (int) hours, (int) minutes, seconds);
}