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
typedef  int /*<<< orphan*/  gdImage ;

/* Variables and functions */

char *
gdImageStringFT (gdImage * im, int *brect, int fg, char *fontlist,
		 double ptsize, double angle, int x, int y, char *string)
{
	return "libgd was not built with FreeType font support\n";
}