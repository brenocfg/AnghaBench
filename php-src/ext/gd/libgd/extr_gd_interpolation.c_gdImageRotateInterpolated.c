#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gdImagePtr ;
struct TYPE_22__ {scalar_t__ trueColor; int saveAlphaFlag; int interpolation_id; int /*<<< orphan*/  sy; int /*<<< orphan*/  sx; int /*<<< orphan*/  alphaBlendingFlag; int /*<<< orphan*/  transparent; int /*<<< orphan*/ * alpha; int /*<<< orphan*/ * blue; int /*<<< orphan*/ * green; int /*<<< orphan*/ * red; } ;

/* Variables and functions */
#define  GD_BICUBIC_FIXED 130 
#define  GD_BILINEAR_FIXED 129 
 int GD_METHOD_COUNT ; 
#define  GD_NEAREST_NEIGHBOUR 128 
 scalar_t__ floorf (float const) ; 
 int fmod (int,int) ; 
 int /*<<< orphan*/  gdEffectReplace ; 
 int /*<<< orphan*/  gdImageCopy (TYPE_1__*,TYPE_1__* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* gdImageCreateTrueColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdImagePaletteToTrueColor (TYPE_1__* const) ; 
 TYPE_1__* gdImageRotate180 (TYPE_1__* const,int /*<<< orphan*/ ) ; 
 TYPE_1__* gdImageRotate270 (TYPE_1__* const,int /*<<< orphan*/ ) ; 
 TYPE_1__* gdImageRotate90 (TYPE_1__* const,int /*<<< orphan*/ ) ; 
 TYPE_1__* gdImageRotateBicubicFixed (TYPE_1__* const,float const,int) ; 
 TYPE_1__* gdImageRotateBilinear (TYPE_1__* const,float const,int) ; 
 TYPE_1__* gdImageRotateGeneric (TYPE_1__* const,float const,int) ; 
 TYPE_1__* gdImageRotateNearestNeighbour (TYPE_1__* const,float const,int) ; 
 int gdMaxColors ; 
 int gdTrueColorAlpha (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

gdImagePtr gdImageRotateInterpolated(const gdImagePtr src, const float angle, int bgcolor)
{
	/* round to two decimals and keep the 100x multiplication to use it in the common square angles
	   case later. Keep the two decimal precisions so smaller rotation steps can be done, useful for
	   slow animations. */
	const int angle_rounded = fmod((int) floorf(angle * 100), 360 * 100);

	if (bgcolor < 0) {
		return NULL;
	}

	/* impact perf a bit, but not that much. Implementation for palette
	   images can be done at a later point.
	*/
	if (src->trueColor == 0) {
		if (bgcolor < gdMaxColors) {
			bgcolor =  gdTrueColorAlpha(src->red[bgcolor], src->green[bgcolor], src->blue[bgcolor], src->alpha[bgcolor]);
		}
		gdImagePaletteToTrueColor(src);
	}

	/* no interpolation needed here */
	switch (angle_rounded) {
		case    0: {
			gdImagePtr dst = gdImageCreateTrueColor(src->sx, src->sy);
			if (dst == NULL) {
				return NULL;
			}
			dst->transparent = src->transparent;
			dst->saveAlphaFlag = 1;
			dst->alphaBlendingFlag = gdEffectReplace;

			gdImageCopy(dst, src, 0,0,0,0,src->sx,src->sy);
			return dst;
		}
		case -27000:
		case   9000:
			return gdImageRotate90(src, 0);
		case -18000:
		case  18000:
			return gdImageRotate180(src, 0);
		case -9000:
		case 27000:
			return gdImageRotate270(src, 0);
	}

	if (src == NULL || src->interpolation_id < 1 || src->interpolation_id > GD_METHOD_COUNT) {
		return NULL;
	}

	switch (src->interpolation_id) {
		case GD_NEAREST_NEIGHBOUR:
			return gdImageRotateNearestNeighbour(src, angle, bgcolor);
			break;

		case GD_BILINEAR_FIXED:
			return gdImageRotateBilinear(src, angle, bgcolor);
			break;

		case GD_BICUBIC_FIXED:
			return gdImageRotateBicubicFixed(src, angle, bgcolor);
			break;

		default:
			return gdImageRotateGeneric(src, angle, bgcolor);
	}
	return NULL;
}