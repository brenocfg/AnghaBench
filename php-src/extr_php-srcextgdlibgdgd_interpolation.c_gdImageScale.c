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
struct TYPE_12__ {int interpolation_id; int /*<<< orphan*/  sy; int /*<<< orphan*/  sx; int /*<<< orphan*/ * interpolation; } ;

/* Variables and functions */
#define  GD_BICUBIC_FIXED 130 
#define  GD_BILINEAR_FIXED 129 
 int GD_METHOD_COUNT ; 
#define  GD_NEAREST_NEIGHBOUR 128 
 TYPE_1__* gdImageScaleBicubicFixed (TYPE_1__* const,unsigned int const,unsigned int const) ; 
 TYPE_1__* gdImageScaleBilinear (TYPE_1__* const,unsigned int const,unsigned int const) ; 
 TYPE_1__* gdImageScaleNearestNeighbour (TYPE_1__* const,unsigned int const,unsigned int const) ; 
 TYPE_1__* gdImageScaleTwoPass (TYPE_1__* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int const,unsigned int const) ; 

gdImagePtr gdImageScale(const gdImagePtr src, const unsigned int new_width, const unsigned int new_height)
{
	gdImagePtr im_scaled = NULL;

	if (src == NULL || src->interpolation_id < 0 || src->interpolation_id > GD_METHOD_COUNT) {
		return NULL;
	}

	if (new_width == 0 || new_height == 0) {
		return NULL;
	}

	switch (src->interpolation_id) {
		/*Special cases, optimized implementations */
		case GD_NEAREST_NEIGHBOUR:
			im_scaled = gdImageScaleNearestNeighbour(src, new_width, new_height);
			break;

		case GD_BILINEAR_FIXED:
			im_scaled = gdImageScaleBilinear(src, new_width, new_height);
			break;

		case GD_BICUBIC_FIXED:
			im_scaled = gdImageScaleBicubicFixed(src, new_width, new_height);
			break;

		/* generic */
		default:
			if (src->interpolation == NULL) {
				return NULL;
			}
			im_scaled = gdImageScaleTwoPass(src, src->sx, src->sy, new_width, new_height);
			break;
	}
	return im_scaled;
}