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
 scalar_t__ isinf (double) ; 
 scalar_t__ isnan (double) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static void
sprintf_double_value(char *ptr, double value, const char *delim)
{
	if (isnan(value))
		sprintf(ptr, "%s%s", "NaN", delim);
	else if (isinf(value))
	{
		if (value < 0)
			sprintf(ptr, "%s%s", "-Infinity", delim);
		else
			sprintf(ptr, "%s%s", "Infinity", delim);
	}
	else
		sprintf(ptr, "%.15g%s", value, delim);
}