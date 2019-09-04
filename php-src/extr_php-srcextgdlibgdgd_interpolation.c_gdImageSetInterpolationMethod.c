#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int gdInterpolationMethod ;
typedef  TYPE_1__* gdImagePtr ;
struct TYPE_3__ {int interpolation_id; int /*<<< orphan*/ * interpolation; } ;

/* Variables and functions */
#define  GD_BELL 149 
#define  GD_BESSEL 148 
#define  GD_BICUBIC 147 
#define  GD_BICUBIC_FIXED 146 
#define  GD_BILINEAR_FIXED 145 
#define  GD_BLACKMAN 144 
#define  GD_BOX 143 
#define  GD_BSPLINE 142 
#define  GD_CATMULLROM 141 
#define  GD_DEFAULT 140 
#define  GD_GAUSSIAN 139 
#define  GD_GENERALIZED_CUBIC 138 
#define  GD_HAMMING 137 
#define  GD_HANNING 136 
#define  GD_HERMITE 135 
 int GD_METHOD_COUNT ; 
#define  GD_MITCHELL 134 
#define  GD_NEAREST_NEIGHBOUR 133 
#define  GD_POWER 132 
#define  GD_QUADRATIC 131 
#define  GD_SINC 130 
#define  GD_TRIANGLE 129 
#define  GD_WEIGHTED4 128 
 int /*<<< orphan*/ * filter_bell ; 
 int /*<<< orphan*/ * filter_bessel ; 
 int /*<<< orphan*/ * filter_bicubic ; 
 int /*<<< orphan*/ * filter_blackman ; 
 int /*<<< orphan*/ * filter_box ; 
 int /*<<< orphan*/ * filter_bspline ; 
 int /*<<< orphan*/ * filter_catmullrom ; 
 int /*<<< orphan*/ * filter_gaussian ; 
 int /*<<< orphan*/ * filter_generalized_cubic ; 
 int /*<<< orphan*/ * filter_hamming ; 
 int /*<<< orphan*/ * filter_hanning ; 
 int /*<<< orphan*/ * filter_hermite ; 
 int /*<<< orphan*/ * filter_mitchell ; 
 int /*<<< orphan*/ * filter_power ; 
 int /*<<< orphan*/ * filter_quadratic ; 
 int /*<<< orphan*/ * filter_sinc ; 
 int /*<<< orphan*/ * filter_triangle ; 

int gdImageSetInterpolationMethod(gdImagePtr im, gdInterpolationMethod id)
{
	if (im == NULL || id < 0 || id > GD_METHOD_COUNT) {
		return 0;
	}

	switch (id) {
		case GD_DEFAULT:
			id = GD_BILINEAR_FIXED;
		/* Optimized versions */
		case GD_BILINEAR_FIXED:
		case GD_BICUBIC_FIXED:
		case GD_NEAREST_NEIGHBOUR:
		case GD_WEIGHTED4:
			im->interpolation = NULL;
			break;

		/* generic versions*/
		case GD_BELL:
			im->interpolation = filter_bell;
			break;
		case GD_BESSEL:
			im->interpolation = filter_bessel;
			break;
		case GD_BICUBIC:
			im->interpolation = filter_bicubic;
			break;
		case GD_BLACKMAN:
			im->interpolation = filter_blackman;
			break;
		case GD_BOX:
			im->interpolation = filter_box;
			break;
		case GD_BSPLINE:
			im->interpolation = filter_bspline;
			break;
		case GD_CATMULLROM:
			im->interpolation = filter_catmullrom;
			break;
		case GD_GAUSSIAN:
			im->interpolation = filter_gaussian;
			break;
		case GD_GENERALIZED_CUBIC:
			im->interpolation = filter_generalized_cubic;
			break;
		case GD_HERMITE:
			im->interpolation = filter_hermite;
			break;
		case GD_HAMMING:
			im->interpolation = filter_hamming;
			break;
		case GD_HANNING:
			im->interpolation = filter_hanning;
			break;
		case GD_MITCHELL:
			im->interpolation = filter_mitchell;
			break;
		case GD_POWER:
			im->interpolation = filter_power;
			break;
		case GD_QUADRATIC:
			im->interpolation = filter_quadratic;
			break;
		case GD_SINC:
			im->interpolation = filter_sinc;
			break;
		case GD_TRIANGLE:
			im->interpolation = filter_triangle;
			break;

		default:
			return 0;
			break;
	}
	im->interpolation_id = id;
	return 1;
}