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
struct fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_CONTROL_3A ; 
 int /*<<< orphan*/  out_8 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dnfb_blank(int blank, struct fb_info *info)
{
	if (blank)
		out_8(AP_CONTROL_3A, 0x0);
	else
		out_8(AP_CONTROL_3A, 0x1);
	return 0;
}