#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gdImagePtr ;
typedef  int /*<<< orphan*/  gdIOCtxPtr ;
struct TYPE_5__ {int enctype; int depth; int width; int height; scalar_t__ topdown; } ;
typedef  TYPE_1__ bmp_info_t ;
struct TYPE_6__ {scalar_t__ off; } ;
typedef  TYPE_2__ bmp_hdr_t ;

/* Variables and functions */
#define  BMP_BI_BITFIELDS 133 
#define  BMP_BI_JPEG 132 
#define  BMP_BI_PNG 131 
#define  BMP_BI_RGB 130 
#define  BMP_BI_RLE4 129 
#define  BMP_BI_RLE8 128 
 int /*<<< orphan*/  BMP_DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdGetByte (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdGetWordLSB (short*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdImageSetPixel (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdSeek (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ gdTell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdTrueColor (int,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int bmp_read_direct(gdImagePtr im, gdIOCtxPtr infile, bmp_info_t *info, bmp_hdr_t *header)
{
	int ypos = 0, xpos = 0, row = 0;
	int padding = 0, alpha = 0, red = 0, green = 0, blue = 0;
	signed short int data = 0;

	switch(info->enctype) {
	case BMP_BI_RGB:
		/* no-op */
		break;

	case BMP_BI_BITFIELDS:
		if (info->depth == 24) {
			BMP_DEBUG(printf("Bitfield compression isn't supported for 24-bit\n"));
			return 1;
		}
		BMP_DEBUG(printf("Currently no bitfield support\n"));
		return 1;
		break;

	case BMP_BI_RLE8:
		if (info->depth != 8) {
			BMP_DEBUG(printf("RLE is only valid for 8-bit images\n"));
			return 1;
		}
		break;
	case BMP_BI_RLE4:
		if (info->depth != 4) {
			BMP_DEBUG(printf("RLE is only valid for 4-bit images\n"));
			return 1;
		}
		break;
	case BMP_BI_JPEG:
	case BMP_BI_PNG:
	default:
		BMP_DEBUG(printf("Unsupported BMP compression format\n"));
		return 1;
	}

	/* There is a chance the data isn't until later, would be weird but it is possible */
	if (gdTell(infile) != header->off) {
		/* Should make sure we don't seek past the file size */
		if (!gdSeek(infile, header->off)) {
			return 1;
		}
	}

	/* The line must be divisible by 4, else its padded with NULLs */
	padding = ((int)(info->depth / 8) * info->width) % 4;
	if (padding) {
		padding = 4 - padding;
	}


	for (ypos = 0; ypos < info->height; ++ypos) {
		if (info->topdown) {
			row = ypos;
		} else {
			row = info->height - ypos - 1;
		}

		for (xpos = 0; xpos < info->width; xpos++) {
			if (info->depth == 16) {
				if (!gdGetWordLSB(&data, infile)) {
					return 1;
				}
				BMP_DEBUG(printf("Data: %X\n", data));
				red = ((data & 0x7C00) >> 10) << 3;
				green = ((data & 0x3E0) >> 5) << 3;
				blue = (data & 0x1F) << 3;
				BMP_DEBUG(printf("R: %d, G: %d, B: %d\n", red, green, blue));
			} else if (info->depth == 24) {
				if (!gdGetByte(&blue, infile) || !gdGetByte(&green, infile) || !gdGetByte(&red, infile)) {
					return 1;
				}
			} else {
				if (!gdGetByte(&blue, infile) || !gdGetByte(&green, infile) || !gdGetByte(&red, infile) || !gdGetByte(&alpha, infile)) {
					return 1;
				}
			}
			/*alpha = gdAlphaMax - (alpha >> 1);*/
			gdImageSetPixel(im, xpos, row, gdTrueColor(red, green, blue));
		}
		for (xpos = padding; xpos > 0; --xpos) {
			if (!gdGetByte(&red, infile)) {
				return 1;
			}
		}
	}

	return 0;
}