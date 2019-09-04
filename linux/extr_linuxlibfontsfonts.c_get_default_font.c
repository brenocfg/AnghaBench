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
typedef  int u32 ;
struct font_desc {int pref; int height; int width; } ;

/* Variables and functions */
 struct font_desc** fonts ; 
 int num_fonts ; 

const struct font_desc *get_default_font(int xres, int yres, u32 font_w,
					 u32 font_h)
{
    int i, c, cc;
    const struct font_desc *f, *g;

    g = NULL;
    cc = -10000;
    for(i=0; i<num_fonts; i++) {
	f = fonts[i];
	c = f->pref;
#if defined(__mc68000__)
#ifdef CONFIG_FONT_PEARL_8x8
	if (MACH_IS_AMIGA && f->idx == PEARL8x8_IDX)
	    c = 100;
#endif
#ifdef CONFIG_FONT_6x11
	if (MACH_IS_MAC && xres < 640 && f->idx == VGA6x11_IDX)
	    c = 100;
#endif
#endif
	if ((yres < 400) == (f->height <= 8))
	    c += 1000;

	if ((font_w & (1 << (f->width - 1))) &&
	    (font_h & (1 << (f->height - 1))))
	    c += 1000;

	if (c > cc) {
	    cc = c;
	    g = f;
	}
    }
    return g;
}