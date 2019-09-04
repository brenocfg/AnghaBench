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
typedef  size_t u32 ;
struct wm_info {size_t freq; size_t wm; } ;
struct i810fb_par {int mem_freq; } ;
struct fb_var_screeninfo {int bits_per_pixel; int pixclock; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct wm_info*) ; 
 struct wm_info* i810_wm_16_100 ; 
 struct wm_info* i810_wm_16_133 ; 
 struct wm_info* i810_wm_24_100 ; 
 struct wm_info* i810_wm_24_133 ; 
 struct wm_info* i810_wm_8_100 ; 
 struct wm_info* i810_wm_8_133 ; 

u32 i810_get_watermark(const struct fb_var_screeninfo *var,
		       struct i810fb_par *par)
{
	struct wm_info *wmark = NULL;
	u32 i, size = 0, pixclock, wm_best = 0, min, diff;

	if (par->mem_freq == 100) {
		switch (var->bits_per_pixel) { 
		case 8:
			wmark = i810_wm_8_100;
			size = ARRAY_SIZE(i810_wm_8_100);
			break;
		case 16:
			wmark = i810_wm_16_100;
			size = ARRAY_SIZE(i810_wm_16_100);
			break;
		case 24:
		case 32:
			wmark = i810_wm_24_100;
			size = ARRAY_SIZE(i810_wm_24_100);
		}
	} else {
		switch(var->bits_per_pixel) {
		case 8:
			wmark = i810_wm_8_133;
			size = ARRAY_SIZE(i810_wm_8_133);
			break;
		case 16:
			wmark = i810_wm_16_133;
			size = ARRAY_SIZE(i810_wm_16_133);
			break;
		case 24:
		case 32:
			wmark = i810_wm_24_133;
			size = ARRAY_SIZE(i810_wm_24_133);
		}
	}

	pixclock = 1000000/var->pixclock;
	min = ~0;
	for (i = 0; i < size; i++) {
		if (pixclock <= wmark[i].freq) 
			diff = wmark[i].freq - pixclock;
		else 
			diff = pixclock - wmark[i].freq;
		if (diff < min) {
			wm_best = wmark[i].wm;
			min = diff;
		}
	}
	return wm_best;		
}