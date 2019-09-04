#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {unsigned int width; unsigned int height; } ;
typedef  TYPE_1__ gdRect ;
typedef  TYPE_2__* gdImagePtr ;
typedef  scalar_t__ gdFixed ;
struct TYPE_11__ {int saveAlphaFlag; int** tpixels; } ;

/* Variables and functions */
 scalar_t__ CLAMP (int,int /*<<< orphan*/ ,int) ; 
 float const M_PI ; 
 int _color_blend (int const,int) ; 
 float cos (float const) ; 
 TYPE_2__* gdImageCreateTrueColor (unsigned int,unsigned int) ; 
 int gdImageSX (TYPE_2__*) ; 
 int gdImageSY (TYPE_2__*) ; 
 int /*<<< orphan*/  gdRotatedImageSize (TYPE_2__*,float const,TYPE_1__*) ; 
 int gdTrueColorAlpha (unsigned char,unsigned char,unsigned char,unsigned char) ; 
 int gdTrueColorGetAlpha (int) ; 
 int gdTrueColorGetBlue (int) ; 
 int gdTrueColorGetGreen (int) ; 
 int gdTrueColorGetRed (int) ; 
 scalar_t__ gd_divfx (scalar_t__,scalar_t__ const) ; 
 scalar_t__ gd_ftofx (float) ; 
 scalar_t__ gd_fxtof (scalar_t__) ; 
 int gd_fxtoi (scalar_t__ const) ; 
 scalar_t__ const gd_itofx (int const) ; 
 scalar_t__ gd_mulfx (scalar_t__ const,scalar_t__ const) ; 
 float sin (float const) ; 

gdImagePtr gdImageRotateBicubicFixed(gdImagePtr src, const float degrees, const int bgColor)
{
	const float _angle = (float)((- degrees / 180.0f) * M_PI);
	const int src_w = gdImageSX(src);
	const int src_h = gdImageSY(src);
	unsigned int new_width, new_height;
	const gdFixed f_0_5 = gd_ftofx(0.5f);
	const gdFixed f_H = gd_itofx(src_h/2);
	const gdFixed f_W = gd_itofx(src_w/2);
	const gdFixed f_cos = gd_ftofx(cos(-_angle));
	const gdFixed f_sin = gd_ftofx(sin(-_angle));
	const gdFixed f_1 = gd_itofx(1);
	const gdFixed f_2 = gd_itofx(2);
	const gdFixed f_4 = gd_itofx(4);
	const gdFixed f_6 = gd_itofx(6);
	const gdFixed f_gama = gd_ftofx(1.04f);

	unsigned int dst_offset_x;
	unsigned int dst_offset_y = 0;
	unsigned int i;
	gdImagePtr dst;
	gdRect bbox;

	gdRotatedImageSize(src, degrees, &bbox);
	new_width = bbox.width;
	new_height = bbox.height;
	dst = gdImageCreateTrueColor(new_width, new_height);

	if (dst == NULL) {
		return NULL;
	}
	dst->saveAlphaFlag = 1;

	for (i=0; i < new_height; i++) {
		unsigned int j;
		dst_offset_x = 0;

		for (j=0; j < new_width; j++) {
			const gdFixed f_i = gd_itofx((int)i - (int)new_height/2);
			const gdFixed f_j = gd_itofx((int)j - (int)new_width/2);
			const gdFixed f_m = gd_mulfx(f_j,f_sin) + gd_mulfx(f_i,f_cos) + f_0_5 + f_H;
			const gdFixed f_n = gd_mulfx(f_j,f_cos) - gd_mulfx(f_i,f_sin) + f_0_5 + f_W;
			const int m = gd_fxtoi(f_m);
			const int n = gd_fxtoi(f_n);

			if ((m > 0) && (m < src_h - 1) && (n > 0) && (n < src_w-1)) {
				const gdFixed f_f = f_m - gd_itofx(m);
				const gdFixed f_g = f_n - gd_itofx(n);
				unsigned int src_offset_x[16], src_offset_y[16];
				unsigned char red, green, blue, alpha;
				gdFixed f_red=0, f_green=0, f_blue=0, f_alpha=0;
				int k;

				if ((m < 1) || (n < 1)) {
					src_offset_x[0] = n;
					src_offset_y[0] = m;
				} else {
					src_offset_x[0] = n - 1;
					src_offset_y[0] = m;
				}

				src_offset_x[1] = n;
				src_offset_y[1] = m;

				if ((m < 1) || (n >= src_w-1)) {
					src_offset_x[2] = - 1;
					src_offset_y[2] = - 1;
				} else {
					src_offset_x[2] = n + 1;
					src_offset_y[2] = m ;
				}

				if ((m < 1) || (n >= src_w-2)) {
					src_offset_x[3] = - 1;
					src_offset_y[3] = - 1;
				} else {
					src_offset_x[3] = n + 1 + 1;
					src_offset_y[3] = m ;
				}

				if (n < 1) {
					src_offset_x[4] = - 1;
					src_offset_y[4] = - 1;
				} else {
					src_offset_x[4] = n - 1;
					src_offset_y[4] = m;
				}

				src_offset_x[5] = n;
				src_offset_y[5] = m;
				if (n >= src_w-1) {
					src_offset_x[6] = - 1;
					src_offset_y[6] = - 1;
				} else {
					src_offset_x[6] = n + 1;
					src_offset_y[6] = m;
				}

				if (n >= src_w-2) {
					src_offset_x[7] = - 1;
					src_offset_y[7] = - 1;
				} else {
					src_offset_x[7] = n + 1 + 1;
					src_offset_y[7] = m;
				}

				if ((m >= src_h-1) || (n < 1)) {
					src_offset_x[8] = - 1;
					src_offset_y[8] = - 1;
				} else {
					src_offset_x[8] = n - 1;
					src_offset_y[8] = m;
				}

				if (m >= src_h-1) {
					src_offset_x[9] = - 1;
					src_offset_y[9] = - 1;
				} else {
					src_offset_x[9] = n;
					src_offset_y[9] = m;
				}

				if ((m >= src_h-1) || (n >= src_w-1)) {
					src_offset_x[10] = - 1;
					src_offset_y[10] = - 1;
				} else {
					src_offset_x[10] = n + 1;
					src_offset_y[10] = m;
				}

				if ((m >= src_h-1) || (n >= src_w-2)) {
					src_offset_x[11] = - 1;
					src_offset_y[11] = - 1;
				} else {
					src_offset_x[11] = n + 1 + 1;
					src_offset_y[11] = m;
				}

				if ((m >= src_h-2) || (n < 1)) {
					src_offset_x[12] = - 1;
					src_offset_y[12] = - 1;
				} else {
					src_offset_x[12] = n - 1;
					src_offset_y[12] = m;
				}

				if (m >= src_h-2) {
					src_offset_x[13] = - 1;
					src_offset_y[13] = - 1;
				} else {
					src_offset_x[13] = n;
					src_offset_y[13] = m;
				}

				if ((m >= src_h-2) || (n >= src_w - 1)) {
					src_offset_x[14] = - 1;
					src_offset_y[14] = - 1;
				} else {
					src_offset_x[14] = n + 1;
					src_offset_y[14] = m;
				}

				if ((m >= src_h-2) || (n >= src_w-2)) {
					src_offset_x[15] = - 1;
					src_offset_y[15] = - 1;
				} else {
					src_offset_x[15] = n  + 1 + 1;
					src_offset_y[15] = m;
				}

				for (k=-1; k<3; k++) {
					const gdFixed f = gd_itofx(k)-f_f;
					const gdFixed f_fm1 = f - f_1;
					const gdFixed f_fp1 = f + f_1;
					const gdFixed f_fp2 = f + f_2;
					gdFixed f_a = 0, f_b = 0,f_c = 0, f_d = 0;
					gdFixed f_RY;
					int l;

					if (f_fp2 > 0) {
						f_a = gd_mulfx(f_fp2,gd_mulfx(f_fp2,f_fp2));
					}

					if (f_fp1 > 0) {
						f_b = gd_mulfx(f_fp1,gd_mulfx(f_fp1,f_fp1));
					}

					if (f > 0) {
						f_c = gd_mulfx(f,gd_mulfx(f,f));
					}

					if (f_fm1 > 0) {
						f_d = gd_mulfx(f_fm1,gd_mulfx(f_fm1,f_fm1));
					}
					f_RY = gd_divfx((f_a-gd_mulfx(f_4,f_b)+gd_mulfx(f_6,f_c)-gd_mulfx(f_4,f_d)),f_6);

					for (l=-1;  l< 3; l++) {
						const gdFixed f = gd_itofx(l) - f_g;
						const gdFixed f_fm1 = f - f_1;
						const gdFixed f_fp1 = f + f_1;
						const gdFixed f_fp2 = f + f_2;
						gdFixed f_a = 0, f_b = 0, f_c = 0, f_d = 0;
						gdFixed f_RX, f_R;
						const int _k = ((k + 1) * 4) + (l + 1);
						register gdFixed f_rs, f_gs, f_bs, f_as;
						register int c;

						if (f_fp2 > 0) {
							f_a = gd_mulfx(f_fp2,gd_mulfx(f_fp2,f_fp2));
						}

						if (f_fp1 > 0) {
							f_b = gd_mulfx(f_fp1,gd_mulfx(f_fp1,f_fp1));
						}

						if (f > 0) {
							f_c = gd_mulfx(f,gd_mulfx(f,f));
						}

						if (f_fm1 > 0) {
							f_d = gd_mulfx(f_fm1,gd_mulfx(f_fm1,f_fm1));
						}

						f_RX = gd_divfx((f_a - gd_mulfx(f_4, f_b) + gd_mulfx(f_6, f_c) - gd_mulfx(f_4, f_d)), f_6);
						f_R = gd_mulfx(f_RY, f_RX);

						if ((src_offset_x[_k] <= 0) || (src_offset_y[_k] <= 0) || (src_offset_y[_k] >= src_h) || (src_offset_x[_k] >= src_w)) {
							c = bgColor;
						} else if ((src_offset_x[_k] <= 1) || (src_offset_y[_k] <= 1) || (src_offset_y[_k] >= (int)src_h - 1) || (src_offset_x[_k] >= (int)src_w - 1)) {
							gdFixed f_127 = gd_itofx(127);
							c = src->tpixels[src_offset_y[_k]][src_offset_x[_k]];
							c = c | (( (int) (gd_fxtof(gd_mulfx(f_R, f_127)) + 50.5f)) << 24);
							c = _color_blend(bgColor, c);
						} else {
							c = src->tpixels[src_offset_y[_k]][src_offset_x[_k]];
						}

						f_rs = gd_itofx(gdTrueColorGetRed(c));
						f_gs = gd_itofx(gdTrueColorGetGreen(c));
						f_bs = gd_itofx(gdTrueColorGetBlue(c));
						f_as = gd_itofx(gdTrueColorGetAlpha(c));

						f_red   += gd_mulfx(f_rs, f_R);
						f_green += gd_mulfx(f_gs, f_R);
						f_blue  += gd_mulfx(f_bs, f_R);
						f_alpha += gd_mulfx(f_as, f_R);
					}
				}

				red   = (unsigned char) CLAMP(gd_fxtoi(gd_mulfx(f_red, f_gama)),   0, 255);
				green = (unsigned char) CLAMP(gd_fxtoi(gd_mulfx(f_green, f_gama)), 0, 255);
				blue  = (unsigned char) CLAMP(gd_fxtoi(gd_mulfx(f_blue, f_gama)),  0, 255);
				alpha = (unsigned char) CLAMP(gd_fxtoi(gd_mulfx(f_alpha, f_gama)), 0, 127);

				dst->tpixels[dst_offset_y][dst_offset_x] =  gdTrueColorAlpha(red, green, blue, alpha);
			} else {
				dst->tpixels[dst_offset_y][dst_offset_x] =  bgColor;
			}
			dst_offset_x++;
		}

		dst_offset_y++;
	}
	return dst;
}