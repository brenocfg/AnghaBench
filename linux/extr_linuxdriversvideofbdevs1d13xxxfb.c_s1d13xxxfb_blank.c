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
struct s1d13xxxfb_par {int display; } ;
struct fb_info {struct s1d13xxxfb_par* par; } ;

/* Variables and functions */
 int EINVAL ; 
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 int /*<<< orphan*/  crt_enable (struct s1d13xxxfb_par*,int) ; 
 int /*<<< orphan*/  dbg (char*,int,struct fb_info*) ; 
 int /*<<< orphan*/  lcd_enable (struct s1d13xxxfb_par*,int) ; 

__attribute__((used)) static int
s1d13xxxfb_blank(int blank_mode, struct fb_info *info)
{
	struct s1d13xxxfb_par *par = info->par;

	dbg("s1d13xxxfb_blank: blank=%d, info=%p\n", blank_mode, info);

	switch (blank_mode) {
		case FB_BLANK_UNBLANK:
		case FB_BLANK_NORMAL:
			if ((par->display & 0x01) != 0)
				lcd_enable(par, 1);
			if ((par->display & 0x02) != 0)
				crt_enable(par, 1);
			break;
		case FB_BLANK_VSYNC_SUSPEND:
		case FB_BLANK_HSYNC_SUSPEND:
			break;
		case FB_BLANK_POWERDOWN:
			lcd_enable(par, 0);
			crt_enable(par, 0);
			break;
		default:
			return -EINVAL;
	}

	/* let fbcon do a soft blank for us */
	return ((blank_mode == FB_BLANK_NORMAL) ? 1 : 0);
}