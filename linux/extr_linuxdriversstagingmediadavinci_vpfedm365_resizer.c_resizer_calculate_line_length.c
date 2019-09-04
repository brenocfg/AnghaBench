#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ MEDIA_BUS_FMT_SGRBG12_1X12 ; 
 scalar_t__ MEDIA_BUS_FMT_UYVY8_2X8 ; 

__attribute__((used)) static void
resizer_calculate_line_length(u32 pix, int width, int height,
			      int *line_len, int *line_len_c)
{
	*line_len = 0;
	*line_len_c = 0;

	if (pix == MEDIA_BUS_FMT_UYVY8_2X8 ||
	    pix == MEDIA_BUS_FMT_SGRBG12_1X12) {
		*line_len = width << 1;
	} else {
		*line_len = width;
		*line_len_c = width;
	}

	/* adjust the line len to be a multiple of 32 */
	*line_len += 31;
	*line_len &= ~0x1f;
	*line_len_c += 31;
	*line_len_c &= ~0x1f;
}