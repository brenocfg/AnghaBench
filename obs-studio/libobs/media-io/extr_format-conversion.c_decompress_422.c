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
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int min_uint32 (int,int) ; 

void decompress_422(const uint8_t *input, uint32_t in_linesize,
		    uint32_t start_y, uint32_t end_y, uint8_t *output,
		    uint32_t out_linesize, bool leading_lum)
{
	uint32_t width_d2 = min_uint32(in_linesize, out_linesize) / 2;
	uint32_t y;

	register const uint32_t *input32;
	register const uint32_t *input32_end;
	register uint32_t *output32;

	if (leading_lum) {
		for (y = start_y; y < end_y; y++) {
			input32 = (const uint32_t *)(input + y * in_linesize);
			input32_end = input32 + width_d2;
			output32 = (uint32_t *)(output + y * out_linesize);

			while (input32 < input32_end) {
				register uint32_t dw = *input32;

				output32[0] = dw;
				dw &= 0xFFFFFF00;
				dw |= (uint8_t)(dw >> 16);
				output32[1] = dw;

				output32 += 2;
				input32++;
			}
		}
	} else {
		for (y = start_y; y < end_y; y++) {
			input32 = (const uint32_t *)(input + y * in_linesize);
			input32_end = input32 + width_d2;
			output32 = (uint32_t *)(output + y * out_linesize);

			while (input32 < input32_end) {
				register uint32_t dw = *input32;

				output32[0] = dw;
				dw &= 0xFFFF00FF;
				dw |= (dw >> 16) & 0xFF00;
				output32[1] = dw;

				output32 += 2;
				input32++;
			}
		}
	}
}