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
struct TYPE_3__ {int x_org; int y_org; } ;
typedef  TYPE_1__ xcb_xcursor_t ;

/* Variables and functions */

void xcb_xcursor_offset(xcb_xcursor_t* data, const int x_org, const int y_org)
{
	data->x_org = x_org;
	data->y_org = y_org;
}