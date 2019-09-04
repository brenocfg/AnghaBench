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
struct fb_var_screeninfo {int /*<<< orphan*/  vmode; int /*<<< orphan*/  activate; void* bits_per_pixel; void* upper_margin; void* vsync_len; void* lower_margin; void* yres_virtual; void* yres; void* left_margin; void* hsync_len; void* right_margin; void* xres_virtual; void* xres; void* pixclock; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_ACTIVATE_NOW ; 
 int /*<<< orphan*/  FB_VMODE_NONINTERLACED ; 
 void* simple_strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int grvga_parse_custom(char *options,
			      struct fb_var_screeninfo *screendata)
{
	char *this_opt;
	int count = 0;
	if (!options || !*options)
		return -1;

	while ((this_opt = strsep(&options, " ")) != NULL) {
		if (!*this_opt)
			continue;

		switch (count) {
		case 0:
			screendata->pixclock = simple_strtoul(this_opt, NULL, 0);
			count++;
			break;
		case 1:
			screendata->xres = screendata->xres_virtual = simple_strtoul(this_opt, NULL, 0);
			count++;
			break;
		case 2:
			screendata->right_margin = simple_strtoul(this_opt, NULL, 0);
			count++;
			break;
		case 3:
			screendata->hsync_len = simple_strtoul(this_opt, NULL, 0);
			count++;
			break;
		case 4:
			screendata->left_margin = simple_strtoul(this_opt, NULL, 0);
			count++;
			break;
		case 5:
			screendata->yres = screendata->yres_virtual = simple_strtoul(this_opt, NULL, 0);
			count++;
			break;
		case 6:
			screendata->lower_margin = simple_strtoul(this_opt, NULL, 0);
			count++;
			break;
		case 7:
			screendata->vsync_len = simple_strtoul(this_opt, NULL, 0);
			count++;
			break;
		case 8:
			screendata->upper_margin = simple_strtoul(this_opt, NULL, 0);
			count++;
			break;
		case 9:
			screendata->bits_per_pixel = simple_strtoul(this_opt, NULL, 0);
			count++;
			break;
		default:
			return -1;
		}
	}
	screendata->activate  = FB_ACTIVATE_NOW;
	screendata->vmode     = FB_VMODE_NONINTERLACED;
	return 0;
}