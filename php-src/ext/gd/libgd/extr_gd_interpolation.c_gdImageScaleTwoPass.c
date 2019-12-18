#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gdImagePtr ;
struct TYPE_12__ {int /*<<< orphan*/  interpolation_id; int /*<<< orphan*/  trueColor; } ;

/* Variables and functions */
 int _gdScaleHoriz (TYPE_1__* const,unsigned int const,unsigned int const,TYPE_1__*,unsigned int const,unsigned int const) ; 
 int _gdScaleVert (TYPE_1__*,unsigned int const,unsigned int const,TYPE_1__*,unsigned int const,unsigned int const) ; 
 TYPE_1__* gdImageCreateTrueColor (unsigned int const,unsigned int const) ; 
 int /*<<< orphan*/  gdImageDestroy (TYPE_1__*) ; 
 int /*<<< orphan*/  gdImagePaletteToTrueColor (TYPE_1__* const) ; 
 int /*<<< orphan*/  gdImageSetInterpolationMethod (TYPE_1__*,int /*<<< orphan*/ ) ; 

gdImagePtr gdImageScaleTwoPass(const gdImagePtr src, const unsigned int src_width, const unsigned int src_height, const unsigned int new_width, const unsigned int new_height)
{
	gdImagePtr tmp_im;
	gdImagePtr dst;
	int scale_pass_res;

	if (new_width == 0 || new_height == 0) {
		return NULL;
	}

	/* Convert to truecolor if it isn't; this code requires it. */
	if (!src->trueColor) {
		gdImagePaletteToTrueColor(src);
	}

	tmp_im = gdImageCreateTrueColor(new_width, src_height);
	if (tmp_im == NULL) {
		return NULL;
	}
	gdImageSetInterpolationMethod(tmp_im, src->interpolation_id);
	scale_pass_res = _gdScaleHoriz(src, src_width, src_height, tmp_im, new_width, src_height);
	if (scale_pass_res != 1) {
		gdImageDestroy(tmp_im);
		return NULL;
	}

	dst = gdImageCreateTrueColor(new_width, new_height);
	if (dst == NULL) {
		gdImageDestroy(tmp_im);
		return NULL;
	}
	gdImageSetInterpolationMethod(dst, src->interpolation_id);
	scale_pass_res = _gdScaleVert(tmp_im, new_width, src_height, dst, new_width, new_height);
	if (scale_pass_res != 1) {
		gdImageDestroy(dst);
		gdImageDestroy(tmp_im);
		return NULL;
	}
	gdImageDestroy(tmp_im);

	return dst;
}