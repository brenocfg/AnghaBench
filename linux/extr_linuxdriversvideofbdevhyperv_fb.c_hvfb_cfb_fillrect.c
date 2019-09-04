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
struct hvfb_par {scalar_t__ synchronous_fb; } ;
struct fb_info {struct hvfb_par* par; } ;
struct fb_fillrect {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfb_fillrect (struct fb_info*,struct fb_fillrect const*) ; 
 int /*<<< orphan*/  synthvid_update (struct fb_info*) ; 

__attribute__((used)) static void hvfb_cfb_fillrect(struct fb_info *p,
			      const struct fb_fillrect *rect)
{
	struct hvfb_par *par = p->par;

	cfb_fillrect(p, rect);
	if (par->synchronous_fb)
		synthvid_update(p);
}