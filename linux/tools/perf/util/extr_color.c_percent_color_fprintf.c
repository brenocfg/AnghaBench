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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int color_fprintf (int /*<<< orphan*/ *,char const*,char const*,double) ; 
 char* get_percent_color (double) ; 

int percent_color_fprintf(FILE *fp, const char *fmt, double percent)
{
	int r;
	const char *color;

	color = get_percent_color(percent);
	r = color_fprintf(fp, color, fmt, percent);

	return r;
}