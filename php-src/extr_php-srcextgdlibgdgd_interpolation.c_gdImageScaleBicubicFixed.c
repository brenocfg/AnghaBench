#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gdImagePtr ;
typedef  scalar_t__ gdFixed ;
struct TYPE_8__ {scalar_t__ trueColor; int saveAlphaFlag; int** tpixels; } ;

/* Variables and functions */
 scalar_t__ CLAMP (long,int /*<<< orphan*/ ,int) ; 
 long MAX (int,unsigned int const) ; 
 TYPE_1__* gdImageCreateTrueColor (long const,long const) ; 
 int /*<<< orphan*/  gdImagePaletteToTrueColor (TYPE_1__*) ; 
 int gdImageSX (TYPE_1__*) ; 
 int gdImageSY (TYPE_1__*) ; 
 int gdTrueColorAlpha (unsigned char,unsigned char,unsigned char,unsigned char) ; 
 int gdTrueColorGetAlpha (int) ; 
 int gdTrueColorGetBlue (int) ; 
 int gdTrueColorGetGreen (int) ; 
 int gdTrueColorGetRed (int) ; 
 scalar_t__ gd_divfx (scalar_t__,scalar_t__ const) ; 
 scalar_t__ gd_ftofx (float) ; 
 long gd_fxtoi (scalar_t__ const) ; 
 scalar_t__ const gd_itofx (long const) ; 
 scalar_t__ gd_mulfx (scalar_t__ const,scalar_t__ const) ; 

gdImagePtr gdImageScaleBicubicFixed(gdImagePtr src, const unsigned int width, const unsigned int height)
{
	const long new_width = MAX(1, width);
	const long new_height = MAX(1, height);
	const int src_w = gdImageSX(src);
	const int src_h = gdImageSY(src);
	const gdFixed f_dx = gd_ftofx((float)src_w / (float)new_width);
	const gdFixed f_dy = gd_ftofx((float)src_h / (float)new_height);
	const gdFixed f_1 = gd_itofx(1);
	const gdFixed f_2 = gd_itofx(2);
	const gdFixed f_4 = gd_itofx(4);
	const gdFixed f_6 = gd_itofx(6);
	const gdFixed f_gamma = gd_ftofx(1.04f);
	gdImagePtr dst;

	unsigned int dst_offset_x;
	unsigned int dst_offset_y = 0;
	long i;

	if (new_width == 0 || new_height == 0) {
		return NULL;
	}

	/* impact perf a bit, but not that much. Implementation for palette
	   images can be done at a later point.
	*/
	if (src->trueColor == 0) {
		gdImagePaletteToTrueColor(src);
	}

	dst = gdImageCreateTrueColor(new_width, new_height);
	if (!dst) {
		return NULL;
	}

	dst->saveAlphaFlag = 1;

	for (i=0; i < new_height; i++) {
		long j;
		dst_offset_x = 0;

		for (j=0; j < new_width; j++) {
			const gdFixed f_a = gd_mulfx(gd_itofx(i), f_dy);
			const gdFixed f_b = gd_mulfx(gd_itofx(j), f_dx);
			const long m = gd_fxtoi(f_a);
			const long n = gd_fxtoi(f_b);
			const gdFixed f_f = f_a - gd_itofx(m);
			const gdFixed f_g = f_b - gd_itofx(n);
			unsigned int src_offset_x[16], src_offset_y[16];
			long k;
			register gdFixed f_red = 0, f_green = 0, f_blue = 0, f_alpha = 0;
			unsigned char red, green, blue, alpha = 0;
			int *dst_row = dst->tpixels[dst_offset_y];

			if ((m < 1) || (n < 1)) {
				src_offset_x[0] = n;
				src_offset_y[0] = m;
			} else {
				src_offset_x[0] = n - 1;
				src_offset_y[0] = m;
			}

			src_offset_x[1] = n;
			src_offset_y[1] = m;

			if ((m < 1) || (n >= src_w - 1)) {
				src_offset_x[2] = n;
				src_offset_y[2] = m;
			} else {
				src_offset_x[2] = n + 1;
				src_offset_y[2] = m;
			}

			if ((m < 1) || (n >= src_w - 2)) {
				src_offset_x[3] = n;
				src_offset_y[3] = m;
			} else {
				src_offset_x[3] = n + 1 + 1;
				src_offset_y[3] = m;
			}

			if (n < 1) {
				src_offset_x[4] = n;
				src_offset_y[4] = m;
			} else {
				src_offset_x[4] = n - 1;
				src_offset_y[4] = m;
			}

			src_offset_x[5] = n;
			src_offset_y[5] = m;
			if (n >= src_w-1) {
				src_offset_x[6] = n;
				src_offset_y[6] = m;
			} else {
				src_offset_x[6] = n + 1;
				src_offset_y[6] = m;
			}

			if (n >= src_w - 2) {
				src_offset_x[7] = n;
				src_offset_y[7] = m;
			} else {
				src_offset_x[7] = n + 1 + 1;
				src_offset_y[7] = m;
			}

			if ((m >= src_h - 1) || (n < 1)) {
				src_offset_x[8] = n;
				src_offset_y[8] = m;
			} else {
				src_offset_x[8] = n - 1;
				src_offset_y[8] = m;
			}

			src_offset_x[9] = n;
			src_offset_y[9] = m;

			if ((m >= src_h-1) || (n >= src_w-1)) {
				src_offset_x[10] = n;
				src_offset_y[10] = m;
			} else {
				src_offset_x[10] = n + 1;
				src_offset_y[10] = m;
			}

			if ((m >= src_h - 1) || (n >= src_w - 2)) {
				src_offset_x[11] = n;
				src_offset_y[11] = m;
			} else {
				src_offset_x[11] = n + 1 + 1;
				src_offset_y[11] = m;
			}

			if ((m >= src_h - 2) || (n < 1)) {
				src_offset_x[12] = n;
				src_offset_y[12] = m;
			} else {
				src_offset_x[12] = n - 1;
				src_offset_y[12] = m;
			}

			src_offset_x[13] = n;
			src_offset_y[13] = m;

			if ((m >= src_h - 2) || (n >= src_w - 1)) {
				src_offset_x[14] = n;
				src_offset_y[14] = m;
			} else {
				src_offset_x[14] = n + 1;
				src_offset_y[14] = m;
			}

			if ((m >= src_h - 2) || (n >= src_w - 2)) {
				src_offset_x[15] = n;
				src_offset_y[15] = m;
			} else {
				src_offset_x[15] = n  + 1 + 1;
				src_offset_y[15] = m;
			}

			for (k = -1; k < 3; k++) {
				const gdFixed f = gd_itofx(k)-f_f;
				const gdFixed f_fm1 = f - f_1;
				const gdFixed f_fp1 = f + f_1;
				const gdFixed f_fp2 = f + f_2;
				register gdFixed f_a = 0, f_b = 0, f_d = 0, f_c = 0;
				register gdFixed f_RY;
				int l;

				if (f_fp2 > 0) f_a = gd_mulfx(f_fp2, gd_mulfx(f_fp2,f_fp2));
				if (f_fp1 > 0) f_b = gd_mulfx(f_fp1, gd_mulfx(f_fp1,f_fp1));
				if (f > 0)     f_c = gd_mulfx(f, gd_mulfx(f,f));
				if (f_fm1 > 0) f_d = gd_mulfx(f_fm1, gd_mulfx(f_fm1,f_fm1));

				f_RY = gd_divfx((f_a - gd_mulfx(f_4,f_b) + gd_mulfx(f_6,f_c) - gd_mulfx(f_4,f_d)),f_6);

				for (l = -1; l < 3; l++) {
					const gdFixed f = gd_itofx(l) - f_g;
					const gdFixed f_fm1 = f - f_1;
					const gdFixed f_fp1 = f + f_1;
					const gdFixed f_fp2 = f + f_2;
					register gdFixed f_a = 0, f_b = 0, f_c = 0, f_d = 0;
					register gdFixed f_RX, f_R, f_rs, f_gs, f_bs, f_ba;
					register int c;
					const int _k = ((k+1)*4) + (l+1);

					if (f_fp2 > 0) f_a = gd_mulfx(f_fp2,gd_mulfx(f_fp2,f_fp2));

					if (f_fp1 > 0) f_b = gd_mulfx(f_fp1,gd_mulfx(f_fp1,f_fp1));

					if (f > 0) f_c = gd_mulfx(f,gd_mulfx(f,f));

					if (f_fm1 > 0) f_d = gd_mulfx(f_fm1,gd_mulfx(f_fm1,f_fm1));

					f_RX = gd_divfx((f_a-gd_mulfx(f_4,f_b)+gd_mulfx(f_6,f_c)-gd_mulfx(f_4,f_d)),f_6);
					f_R = gd_mulfx(f_RY,f_RX);

					c = src->tpixels[*(src_offset_y + _k)][*(src_offset_x + _k)];
					f_rs = gd_itofx(gdTrueColorGetRed(c));
					f_gs = gd_itofx(gdTrueColorGetGreen(c));
					f_bs = gd_itofx(gdTrueColorGetBlue(c));
					f_ba = gd_itofx(gdTrueColorGetAlpha(c));

					f_red += gd_mulfx(f_rs,f_R);
					f_green += gd_mulfx(f_gs,f_R);
					f_blue += gd_mulfx(f_bs,f_R);
					f_alpha += gd_mulfx(f_ba,f_R);
				}
			}

			red    = (unsigned char) CLAMP(gd_fxtoi(gd_mulfx(f_red,   f_gamma)),  0, 255);
			green  = (unsigned char) CLAMP(gd_fxtoi(gd_mulfx(f_green, f_gamma)),  0, 255);
			blue   = (unsigned char) CLAMP(gd_fxtoi(gd_mulfx(f_blue,  f_gamma)),  0, 255);
			alpha  = (unsigned char) CLAMP(gd_fxtoi(gd_mulfx(f_alpha,  f_gamma)), 0, 127);

			*(dst_row + dst_offset_x) = gdTrueColorAlpha(red, green, blue, alpha);

			dst_offset_x++;
		}
		dst_offset_y++;
	}
	return dst;
}