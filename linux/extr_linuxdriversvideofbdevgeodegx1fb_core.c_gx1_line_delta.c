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

__attribute__((used)) static int gx1_line_delta(int xres, int bpp)
{
	int line_delta = xres * (bpp >> 3);

	if (line_delta > 2048)
		line_delta = 4096;
	else if (line_delta > 1024)
		line_delta = 2048;
	else
		line_delta = 1024;
	return line_delta;
}