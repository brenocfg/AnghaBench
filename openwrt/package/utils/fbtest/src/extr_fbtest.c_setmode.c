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
struct vidsize {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct pixelformat {int /*<<< orphan*/  transp; int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; int /*<<< orphan*/  bpp; } ;
struct fb_var_screeninfo {int /*<<< orphan*/  transp; int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; int /*<<< orphan*/  bits_per_pixel; int /*<<< orphan*/  yres_virtual; int /*<<< orphan*/  yres; int /*<<< orphan*/  xres_virtual; int /*<<< orphan*/  xres; } ;

/* Variables and functions */
 int /*<<< orphan*/  FBIOGET_VSCREENINFO ; 
 int /*<<< orphan*/  FBIOPUT_VSCREENINFO ; 
 int ioctl (int,int /*<<< orphan*/ ,struct fb_var_screeninfo*) ; 

int setmode(int fbd, const struct pixelformat *pixf,const struct vidsize *vids){
	struct fb_var_screeninfo var;
	int stat;
	stat = ioctl (fbd, FBIOGET_VSCREENINFO,&var);
	if (stat<0) return -2;
	
	var.xres= vids->width;
	var.xres_virtual = vids->width;
	var.yres= vids->height;
	var.yres_virtual = vids->height;
	
	var.bits_per_pixel = pixf->bpp;
	var.red = pixf->red;
	var.green = pixf->green;
	var.blue = pixf->blue;
	var.transp = pixf->transp;

	stat = ioctl (fbd, FBIOPUT_VSCREENINFO,&var);
	if (stat<0) return -1;
	return 0;
}