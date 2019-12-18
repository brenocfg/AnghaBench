#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gdImagePtr ;
struct TYPE_5__ {int** tpixels; int sx; int sy; int transparent; int trueColor; int alphaBlendingFlag; int thick; int cx2; int cy2; int /*<<< orphan*/  interpolation_id; int /*<<< orphan*/ * interpolation; void* res_y; void* res_x; scalar_t__ cy1; scalar_t__ cx1; scalar_t__ AA; scalar_t__ saveAlphaFlag; scalar_t__ interlace; scalar_t__ style; scalar_t__ tile; scalar_t__ brush; scalar_t__ polyAllocated; scalar_t__ polyInts; } ;
typedef  TYPE_1__ gdImage ;

/* Variables and functions */
 int /*<<< orphan*/  GD_BILINEAR_FIXED ; 
 void* GD_RESOLUTION ; 
 scalar_t__ gdCalloc (int,int) ; 
 scalar_t__ gdMalloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ overflow2 (int,int) ; 

gdImagePtr gdImageCreateTrueColor (int sx, int sy)
{
	int i;
	gdImagePtr im;

	if (overflow2(sx, sy)) {
		return NULL;
	}
	if (overflow2(sizeof(int *), sy)) {
		return NULL;
	}
	if (overflow2(sizeof(int), sx)) {
		return NULL;
	}

	im = (gdImage *) gdMalloc(sizeof(gdImage));
	memset(im, 0, sizeof(gdImage));
	im->tpixels = (int **) gdMalloc(sizeof(int *) * sy);
	im->polyInts = 0;
	im->polyAllocated = 0;
	im->brush = 0;
	im->tile = 0;
	im->style = 0;
	for (i = 0; i < sy; i++) {
		im->tpixels[i] = (int *) gdCalloc(sx, sizeof(int));
	}
	im->sx = sx;
	im->sy = sy;
	im->transparent = (-1);
	im->interlace = 0;
	im->trueColor = 1;
	/* 2.0.2: alpha blending is now on by default, and saving of alpha is
	 * off by default. This allows font antialiasing to work as expected
	 * on the first try in JPEGs -- quite important -- and also allows
	 * for smaller PNGs when saving of alpha channel is not really
	 * desired, which it usually isn't!
	 */
	im->saveAlphaFlag = 0;
	im->alphaBlendingFlag = 1;
	im->thick = 1;
	im->AA = 0;
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