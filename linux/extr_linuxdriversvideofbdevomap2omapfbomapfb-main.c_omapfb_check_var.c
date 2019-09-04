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
struct omapfb_info {int /*<<< orphan*/  region; int /*<<< orphan*/  id; } ;
struct fb_var_screeninfo {int dummy; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 struct omapfb_info* FB2OFB (struct fb_info*) ; 
 int check_fb_var (struct fb_info*,struct fb_var_screeninfo*) ; 
 int /*<<< orphan*/  omapfb_get_mem_region (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omapfb_put_mem_region (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omapfb_check_var(struct fb_var_screeninfo *var, struct fb_info *fbi)
{
	struct omapfb_info *ofbi = FB2OFB(fbi);
	int r;

	DBG("check_var(%d)\n", FB2OFB(fbi)->id);

	omapfb_get_mem_region(ofbi->region);

	r = check_fb_var(fbi, var);

	omapfb_put_mem_region(ofbi->region);

	return r;
}