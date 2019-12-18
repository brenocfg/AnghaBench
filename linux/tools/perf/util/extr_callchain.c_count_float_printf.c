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
 int scnprintf (char*,int,char*,char*,char const*,float) ; 

__attribute__((used)) static int count_float_printf(int idx, const char *str, float value,
			      char *bf, int bfsize, float threshold)
{
	int printed;

	if (threshold != 0.0 && value < threshold)
		return 0;

	printed = scnprintf(bf, bfsize, "%s%s:%.1f%%", (idx) ? " " : " (", str, value);

	return printed;
}