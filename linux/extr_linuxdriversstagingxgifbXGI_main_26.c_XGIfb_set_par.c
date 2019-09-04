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
struct fb_info {int /*<<< orphan*/  fix; int /*<<< orphan*/  var; } ;

/* Variables and functions */
 int XGIfb_do_set_var (int /*<<< orphan*/ *,int,struct fb_info*) ; 
 int /*<<< orphan*/  XGIfb_get_fix (int /*<<< orphan*/ *,int,struct fb_info*) ; 

__attribute__((used)) static int XGIfb_set_par(struct fb_info *info)
{
	int err;

	err = XGIfb_do_set_var(&info->var, 1, info);
	if (err)
		return err;
	XGIfb_get_fix(&info->fix, -1, info);
	return 0;
}