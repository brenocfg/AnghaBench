#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gdImagePtr ;
typedef  int /*<<< orphan*/  gdIOCtxPtr ;
struct TYPE_7__ {int depth; int height; int width; } ;
typedef  TYPE_2__ bmp_info_t ;
struct TYPE_6__ {scalar_t__* open; } ;

/* Variables and functions */
 int BMP_RLE_COMMAND ; 
 int BMP_RLE_DELTA ; 
 int BMP_RLE_ENDOFBITMAP ; 
 int BMP_RLE_ENDOFLINE ; 
 int /*<<< orphan*/  gdGetByte (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdImageSetPixel (TYPE_1__*,int,int,int) ; 

__attribute__((used)) static int bmp_read_rle(gdImagePtr im, gdIOCtxPtr infile, bmp_info_t *info)
{
	int ypos = 0, xpos = 0, row = 0, index = 0;
	int rle_length = 0, rle_data = 0;
	int padding = 0;
	int i = 0, j = 0;
	int pixels_per_byte = 8 / info->depth;

	for (ypos = 0; ypos < info->height && xpos <= info->width;) {
		if (!gdGetByte(&rle_length, infile) || !gdGetByte(&rle_data, infile)) {
			return 1;
		}
		row = info->height - ypos - 1;

		if (rle_length != BMP_RLE_COMMAND) {
			if (im->open[rle_data]) {
				im->open[rle_data] = 0;
			}

			for (i = 0; (i < rle_length) && (xpos < info->width);) {
				for (j = 1; (j <= pixels_per_byte) && (xpos < info->width) && (i < rle_length); j++, xpos++, i++) {
					index = (rle_data & (((1 << info->depth) - 1) << (8 - (j * info->depth)))) >> (8 - (j * info->depth));
					if (im->open[index]) {
						im->open[index] = 0;
					}
					gdImageSetPixel(im, xpos, row, index);
				}
			}
		} else if (rle_length == BMP_RLE_COMMAND && rle_data > 2) {
			/* Uncompressed RLE needs to be even */
			padding = 0;
			for (i = 0; (i < rle_data) && (xpos < info->width); i += pixels_per_byte) {
				int max_pixels = pixels_per_byte;

				if (!gdGetByte(&index, infile)) {
					return 1;
				}
				padding++;

				if (rle_data - i < max_pixels) {
					max_pixels = rle_data - i;
				}

				for (j = 1; (j <= max_pixels)  && (xpos < info->width); j++, xpos++) {
					int temp = (index >> (8 - (j * info->depth))) & ((1 << info->depth) - 1);
					if (im->open[temp]) {
						im->open[temp] = 0;
					}
					gdImageSetPixel(im, xpos, row, temp);
				}
			}

			/* Make sure the bytes read are even */
			if (padding % 2 && !gdGetByte(&index, infile)) {
				return 1;
			}
		} else if (rle_length == BMP_RLE_COMMAND && rle_data == BMP_RLE_ENDOFLINE) {
			/* Next Line */
			xpos = 0;
			ypos++;
		} else if (rle_length == BMP_RLE_COMMAND && rle_data == BMP_RLE_DELTA) {
			/* Delta Record, used for bmp files that contain other data*/
			if (!gdGetByte(&rle_length, infile) || !gdGetByte(&rle_data, infile)) {
				return 1;
			}
			xpos += rle_length;
			ypos += rle_data;
		} else if (rle_length == BMP_RLE_COMMAND && rle_data == BMP_RLE_ENDOFBITMAP) {
			/* End of bitmap */
			break;
		}
	}
	return 0;
}