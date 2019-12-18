#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int width; int height; } ;
typedef  TYPE_1__ gdRect ;
typedef  TYPE_2__* gdImagePtr ;
typedef  scalar_t__ gdFixed ;
struct TYPE_12__ {int saveAlphaFlag; int** tpixels; } ;

/* Variables and functions */
 scalar_t__ M_PI ; 
 int _color_blend (int const,int) ; 
 float cos (float) ; 
 TYPE_2__* gdImageCreateTrueColor (int,int) ; 
 int gdImageSX (TYPE_2__*) ; 
 int gdImageSY (TYPE_2__*) ; 
 int /*<<< orphan*/  gdRotatedImageSize (TYPE_2__*,float const,TYPE_1__*) ; 
 int gdTrueColorGetAlpha (int) ; 
 scalar_t__ gd_divfx (scalar_t__ const,scalar_t__ const) ; 
 scalar_t__ gd_ftofx (float) ; 
 int gd_fxtof (scalar_t__ const) ; 
 long gd_fxtoi (scalar_t__) ; 
 void* gd_itofx (int const) ; 
 scalar_t__ const gd_mulfx (scalar_t__,scalar_t__ const) ; 
 void* getPixelInterpolated (TYPE_2__*,long,long,int const) ; 
 float sin (float) ; 

gdImagePtr gdImageRotateGeneric(gdImagePtr src, const float degrees, const int bgColor)
{
	float _angle = ((float) (-degrees / 180.0f) * (float)M_PI);
	const int src_w  = gdImageSX(src);
	const int src_h = gdImageSY(src);
	const gdFixed f_0_5 = gd_ftofx(0.5f);
	const gdFixed f_H = gd_itofx(src_h/2);
	const gdFixed f_W = gd_itofx(src_w/2);
	const gdFixed f_cos = gd_ftofx(cos(-_angle));
	const gdFixed f_sin = gd_ftofx(sin(-_angle));

	unsigned int dst_offset_x;
	unsigned int dst_offset_y = 0;
	unsigned int i;
	gdImagePtr dst;
	int new_width, new_height;
	gdRect bbox;

	const gdFixed f_slop_y = f_sin;
	const gdFixed f_slop_x = f_cos;
	const gdFixed f_slop = f_slop_x > 0 && f_slop_y > 0 ?
							(f_slop_x > f_slop_y ? gd_divfx(f_slop_y, f_slop_x) : gd_divfx(f_slop_x, f_slop_y))
						: 0;


	if (bgColor < 0) {
		return NULL;
	}

    gdRotatedImageSize(src, degrees, &bbox);
    new_width = bbox.width;
    new_height = bbox.height;

	dst = gdImageCreateTrueColor(new_width, new_height);
	if (!dst) {
		return NULL;
	}
	dst->saveAlphaFlag = 1;

	for (i = 0; i < new_height; i++) {
		unsigned int j;
		dst_offset_x = 0;
		for (j = 0; j < new_width; j++) {
			gdFixed f_i = gd_itofx((int)i - (int)new_height/ 2);
			gdFixed f_j = gd_itofx((int)j - (int)new_width / 2);
			gdFixed f_m = gd_mulfx(f_j,f_sin) + gd_mulfx(f_i,f_cos) + f_0_5 + f_H;
			gdFixed f_n = gd_mulfx(f_j,f_cos) - gd_mulfx(f_i,f_sin) + f_0_5 + f_W;
			long m = gd_fxtoi(f_m);
			long n = gd_fxtoi(f_n);

			if ((n <= 0) || (m <= 0) || (m >= src_h) || (n >= src_w)) {
				dst->tpixels[dst_offset_y][dst_offset_x++] = bgColor;
			} else if ((n <= 1) || (m <= 1) || (m >= src_h - 1) || (n >= src_w - 1)) {
				register int c = getPixelInterpolated(src, n, m, bgColor);
				c = c | (( gdTrueColorGetAlpha(c) + ((int)(127* gd_fxtof(f_slop)))) << 24);

				dst->tpixels[dst_offset_y][dst_offset_x++] = _color_blend(bgColor, c);
			} else {
				dst->tpixels[dst_offset_y][dst_offset_x++] = getPixelInterpolated(src, n, m, bgColor);
			}
		}
		dst_offset_y++;
	}
	return dst;
}