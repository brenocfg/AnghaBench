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
struct w100fb_par {unsigned long hsync_len; scalar_t__ blanked; } ;
struct fb_info {struct w100fb_par* par; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct fb_info* dev_get_drvdata (struct device*) ; 

unsigned long w100fb_get_hsynclen(struct device *dev)
{
	struct fb_info *info = dev_get_drvdata(dev);
	struct w100fb_par *par=info->par;

	/* If display is blanked/suspended, hsync isn't active */
	if (par->blanked)
		return 0;
	else
		return par->hsync_len;
}