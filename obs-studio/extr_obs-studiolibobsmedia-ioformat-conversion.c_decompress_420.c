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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */

void decompress_420(
		const uint8_t *const input[], const uint32_t in_linesize[],
		uint32_t start_y, uint32_t end_y,
		uint8_t *output, uint32_t out_linesize)
{
	uint32_t start_y_d2 = start_y/2;
	uint32_t width_d2   = in_linesize[0]/2;
	uint32_t height_d2  = end_y/2;
	uint32_t y;

	for (y = start_y_d2; y < height_d2; y++) {
		const uint8_t *chroma0 = input[1] + y * in_linesize[1];
		const uint8_t *chroma1 = input[2] + y * in_linesize[2];
		register const uint8_t *lum0, *lum1;
		register uint32_t *output0, *output1;
		uint32_t x;

		lum0 = input[0] + y * 2 * in_linesize[0];
		lum1 = lum0 + in_linesize[0];
		output0 = (uint32_t*)(output + y * 2 * out_linesize);
		output1 = (uint32_t*)((uint8_t*)output0 + out_linesize);

		for (x = 0; x < width_d2; x++) {
			uint32_t out;
			out = (*(chroma0++) << 8) | *(chroma1++);

			*(output0++) = (*(lum0++) << 16) | out;
			*(output0++) = (*(lum0++) << 16) | out;

			*(output1++) = (*(lum1++) << 16) | out;
			*(output1++) = (*(lum1++) << 16) | out;
		}
	}
}