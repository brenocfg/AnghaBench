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
struct usb_mixer_elem_info {int res; int min; int max; } ;

/* Variables and functions */

__attribute__((used)) static int get_relative_value(struct usb_mixer_elem_info *cval, int val)
{
	if (!cval->res)
		cval->res = 1;
	if (val < cval->min)
		return 0;
	else if (val >= cval->max)
		return (cval->max - cval->min + cval->res - 1) / cval->res;
	else
		return (val - cval->min) / cval->res;
}