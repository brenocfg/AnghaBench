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
struct fb_bitfield {scalar_t__ length; scalar_t__ offset; scalar_t__ msb_right; } ;

/* Variables and functions */

__attribute__((used)) static bool cmp_component(struct fb_bitfield *f1, struct fb_bitfield *f2)
{
	return f1->length == f2->length &&
		f1->offset == f2->offset &&
		f1->msb_right == f2->msb_right;
}