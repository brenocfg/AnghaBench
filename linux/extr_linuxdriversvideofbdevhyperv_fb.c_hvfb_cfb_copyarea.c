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
struct fb_copyarea {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfb_copyarea (struct fb_info*,struct fb_copyarea const*) ; 
 int /*<<< orphan*/  synthvid_update (struct fb_info*) ; 

__attribute__((used)) static void hvfb_cfb_copyarea(struct fb_info *p,
			      const struct fb_copyarea *area)
{
	struct hvfb_par *par = p->par;

	cfb_copyarea(p, area);
	if (par->synchronous_fb)
		synthvid_update(p);
}