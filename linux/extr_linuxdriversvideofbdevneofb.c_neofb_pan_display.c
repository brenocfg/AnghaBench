#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vgastate {int /*<<< orphan*/  vgabase; } ;
struct neofb_par {struct vgastate state; } ;
struct fb_var_screeninfo {int yoffset; int xoffset; } ;
struct TYPE_2__ {int xres_virtual; int bits_per_pixel; } ;
struct fb_info {TYPE_1__ var; struct neofb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  neoLock (struct vgastate*) ; 
 int /*<<< orphan*/  neoUnlock () ; 
 int vga_rgfx (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vga_wcrt (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  vga_wgfx (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int neofb_pan_display(struct fb_var_screeninfo *var,
			     struct fb_info *info)
{
	struct neofb_par *par = info->par;
	struct vgastate *state = &par->state;
	int oldExtCRTDispAddr;
	int Base;

	DBG("neofb_update_start");

	Base = (var->yoffset * info->var.xres_virtual + var->xoffset) >> 2;
	Base *= (info->var.bits_per_pixel + 7) / 8;

	neoUnlock();

	/*
	 * These are the generic starting address registers.
	 */
	vga_wcrt(state->vgabase, 0x0C, (Base & 0x00FF00) >> 8);
	vga_wcrt(state->vgabase, 0x0D, (Base & 0x00FF));

	/*
	 * Make sure we don't clobber some other bits that might already
	 * have been set. NOTE: NM2200 has a writable bit 3, but it shouldn't
	 * be needed.
	 */
	oldExtCRTDispAddr = vga_rgfx(NULL, 0x0E);
	vga_wgfx(state->vgabase, 0x0E, (((Base >> 16) & 0x0f) | (oldExtCRTDispAddr & 0xf0)));

	neoLock(state);

	return 0;
}