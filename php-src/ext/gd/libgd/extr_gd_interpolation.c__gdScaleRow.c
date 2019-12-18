#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* gdImagePtr ;
struct TYPE_9__ {TYPE_1__* ContribRow; } ;
struct TYPE_8__ {int** tpixels; } ;
struct TYPE_7__ {int Left; int Right; double* Weights; } ;
typedef  TYPE_3__ LineContribType ;

/* Variables and functions */
 int gdTrueColorAlpha (unsigned char,unsigned char,unsigned char,unsigned char) ; 
 scalar_t__ gdTrueColorGetAlpha (int) ; 
 scalar_t__ gdTrueColorGetBlue (int) ; 
 scalar_t__ gdTrueColorGetGreen (int) ; 
 scalar_t__ gdTrueColorGetRed (int) ; 

__attribute__((used)) static inline void _gdScaleRow(gdImagePtr pSrc,  unsigned int src_width, gdImagePtr dst, unsigned int dst_width, unsigned int row, LineContribType *contrib)
{
    int *p_src_row = pSrc->tpixels[row];
    int *p_dst_row = dst->tpixels[row];
	unsigned int x;

    for (x = 0; x < dst_width - 1; x++) {
		register unsigned char r = 0, g = 0, b = 0, a = 0;
        const int left = contrib->ContribRow[x].Left;
        const int right = contrib->ContribRow[x].Right;
		int i;

		/* Accumulate each channel */
        for (i = left; i <= right; i++) {
			const int left_channel = i - left;
            r += (unsigned char)(contrib->ContribRow[x].Weights[left_channel] * (double)(gdTrueColorGetRed(p_src_row[i])));
            g += (unsigned char)(contrib->ContribRow[x].Weights[left_channel] * (double)(gdTrueColorGetGreen(p_src_row[i])));
            b += (unsigned char)(contrib->ContribRow[x].Weights[left_channel] * (double)(gdTrueColorGetBlue(p_src_row[i])));
			a += (unsigned char)(contrib->ContribRow[x].Weights[left_channel] * (double)(gdTrueColorGetAlpha(p_src_row[i])));
        }
        p_dst_row[x] = gdTrueColorAlpha(r, g, b, a);
    }
}