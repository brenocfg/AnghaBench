#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gdImagePtr ;
typedef  int /*<<< orphan*/  gdIOCtxPtr ;
struct TYPE_10__ {scalar_t__ enctype; int numcolors; scalar_t__ type; int width; int height; scalar_t__ topdown; } ;
typedef  TYPE_2__ bmp_info_t ;
struct TYPE_11__ {scalar_t__ off; } ;
typedef  TYPE_3__ bmp_hdr_t ;
struct TYPE_9__ {int colorsTotal; scalar_t__* open; } ;

/* Variables and functions */
 scalar_t__ BMP_BI_RGB ; 
 scalar_t__ BMP_PALETTE_4 ; 
 scalar_t__ bmp_read_palette (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gdGetByte (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdImageSetPixel (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  gdSeek (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ gdTell (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bmp_read_1bit(gdImagePtr im, gdIOCtxPtr infile, bmp_info_t *info, bmp_hdr_t *header)
{
	int ypos = 0, xpos = 0, row = 0, index = 0;
	int padding = 0, current_byte = 0, bit = 0;

	if (info->enctype != BMP_BI_RGB) {
		return 1;
	}

	if (!info->numcolors) {
		info->numcolors = 2;
	} else if (info->numcolors < 0 || info->numcolors > 2) {
		return 1;
	}

	if (bmp_read_palette(im, infile, info->numcolors, (info->type == BMP_PALETTE_4))) {
		return 1;
	}

	im->colorsTotal = info->numcolors;

	/* There is a chance the data isn't until later, would be weird but it is possible */
	if (gdTell(infile) != header->off) {
		/* Should make sure we don't seek past the file size */
		if (!gdSeek(infile, header->off)) {
			return 1;
		}
	}

	/* The line must be aligned on a 32 bits word, else it is padded with zeros */
	padding = (info->width + 7) / 8 % 4;
	if (padding) {
		padding = 4 - padding;
	}

	for (ypos = 0; ypos < info->height; ++ypos) {
		if (info->topdown) {
			row = ypos;
		} else {
			row = info->height - ypos - 1;
		}

		for (xpos = 0; xpos < info->width; xpos += 8) {
			/* Bitmaps are always aligned in bytes so we'll never overflow */
			if (!gdGetByte(&current_byte, infile)) {
				return 1;
			}

			for (bit = 0; bit < 8; bit++) {
				index = ((current_byte & (0x80 >> bit)) != 0 ? 0x01 : 0x00);
				if (im->open[index]) {
					im->open[index] = 0;
				}
				gdImageSetPixel(im, xpos + bit, row, index);
				/* No need to read anything extra */
				if ((xpos + bit) >= info->width) {
					break;
				}
			}
		}

		for (xpos = padding; xpos > 0; --xpos) {
			if (!gdGetByte(&index, infile)) {
				return 1;
			}
		}
	}
	return 0;
}