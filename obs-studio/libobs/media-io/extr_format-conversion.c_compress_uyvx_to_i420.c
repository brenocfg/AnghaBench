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
typedef  int /*<<< orphan*/  __m128i ;

/* Variables and functions */
 int /*<<< orphan*/  _mm_load_si128 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  _mm_set1_epi16 (int) ; 
 int /*<<< orphan*/  _mm_set1_epi32 (int) ; 
 int min_uint32 (int,int const) ; 
 int /*<<< orphan*/  pack_ch_2plane (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pack_shift (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void compress_uyvx_to_i420(const uint8_t *input, uint32_t in_linesize,
			   uint32_t start_y, uint32_t end_y, uint8_t *output[],
			   const uint32_t out_linesize[])
{
	uint8_t *lum_plane = output[0];
	uint8_t *u_plane = output[1];
	uint8_t *v_plane = output[2];
	uint32_t width = min_uint32(in_linesize, out_linesize[0]);
	uint32_t y;

	__m128i lum_mask = _mm_set1_epi32(0x0000FF00);
	__m128i uv_mask = _mm_set1_epi16(0x00FF);

	for (y = start_y; y < end_y; y += 2) {
		uint32_t y_pos = y * in_linesize;
		uint32_t chroma_y_pos = (y >> 1) * out_linesize[1];
		uint32_t lum_y_pos = y * out_linesize[0];
		uint32_t x;

		for (x = 0; x < width; x += 4) {
			const uint8_t *img = input + y_pos + x * 4;
			uint32_t lum_pos0 = lum_y_pos + x;
			uint32_t lum_pos1 = lum_pos0 + out_linesize[0];

			__m128i line1 = _mm_load_si128((const __m128i *)img);
			__m128i line2 = _mm_load_si128(
				(const __m128i *)(img + in_linesize));

			pack_shift(lum_plane, lum_pos0, lum_pos1, line1, line2,
				   lum_mask, 1);
			pack_ch_2plane(u_plane, v_plane,
				       chroma_y_pos + (x >> 1), line1, line2,
				       uv_mask);
		}
	}
}