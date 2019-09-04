#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gdImagePtr ;
struct TYPE_4__ {unsigned char** pixels; int sx; int sy; int transparent; int thick; int* open; int cx2; int cy2; int /*<<< orphan*/  interpolation_id; int /*<<< orphan*/ * interpolation; void* res_y; void* res_x; scalar_t__ cy1; scalar_t__ cx1; scalar_t__ tpixels; scalar_t__ trueColor; scalar_t__* blue; scalar_t__* green; scalar_t__* red; scalar_t__ AA; scalar_t__ interlace; scalar_t__ colorsTotal; scalar_t__ style; scalar_t__ tile; scalar_t__ brush; scalar_t__ polyAllocated; scalar_t__ polyInts; } ;
typedef  TYPE_1__ gdImage ;

/* Variables and functions */
 int /*<<< orphan*/  GD_BILINEAR_FIXED ; 
 void* GD_RESOLUTION ; 
 scalar_t__ gdCalloc (int,int) ; 
 scalar_t__ gdMalloc (int) ; 
 int gdMaxColors ; 
 scalar_t__ overflow2 (int,int) ; 

gdImagePtr gdImageCreate (int sx, int sy)
{
	int i;
	gdImagePtr im;

	if (overflow2(sx, sy)) {
		return NULL;
	}
	if (overflow2(sizeof(unsigned char *), sy)) {
		return NULL;
	}
	if (overflow2(sizeof(unsigned char), sx)) {
		return NULL;
	}

	im = (gdImage *) gdCalloc(1, sizeof(gdImage));

	/* Row-major ever since gd 1.3 */
	im->pixels = (unsigned char **) gdMalloc(sizeof(unsigned char *) * sy);
	im->polyInts = 0;
	im->polyAllocated = 0;
	im->brush = 0;
	im->tile = 0;
	im->style = 0;
	for (i = 0; i < sy; i++) {
		/* Row-major ever since gd 1.3 */
		im->pixels[i] = (unsigned char *) gdCalloc(sx, sizeof(unsigned char));
	}
	im->sx = sx;
	im->sy = sy;
	im->colorsTotal = 0;
	im->transparent = (-1);
	im->interlace = 0;
	im->thick = 1;
	im->AA = 0;
	for (i = 0; i < gdMaxColors; i++) {
		im->open[i] = 1;
		im->red[i] = 0;
		im->green[i] = 0;
		im->blue[i] = 0;
	}
	im->trueColor = 0;
	im->tpixels = 0;
	im->cx1 = 0;
	im->cy1 = 0;
	im->cx2 = im->sx - 1;
	im->cy2 = im->sy - 1;
	im->res_x = GD_RESOLUTION;
	im->res_y = GD_RESOLUTION;
	im->interpolation = NULL;
	im->interpolation_id = GD_BILINEAR_FIXED;
	return im;
}