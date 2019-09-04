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
struct fb_cursor {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int vmlfb_cursor(struct fb_info *info, struct fb_cursor *cursor)
{
	return -EINVAL;	/* just to force soft_cursor() call */
}