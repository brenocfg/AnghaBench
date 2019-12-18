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
 int color_snprintf (char*,size_t,char const*,char const*,double) ; 
 char* get_percent_color (double) ; 

int value_color_snprintf(char *bf, size_t size, const char *fmt, double value)
{
	const char *color = get_percent_color(value);
	return color_snprintf(bf, size, color, fmt, value);
}