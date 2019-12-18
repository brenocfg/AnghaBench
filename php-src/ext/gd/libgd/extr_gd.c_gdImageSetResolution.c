#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gdImagePtr ;
struct TYPE_3__ {unsigned int res_x; unsigned int res_y; } ;

/* Variables and functions */

void gdImageSetResolution(gdImagePtr im, const unsigned int res_x, const unsigned int res_y)
{
	if (res_x > 0) im->res_x = res_x;
	if (res_y > 0) im->res_y = res_y;
}