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
typedef  int /*<<< orphan*/  uint16_t ;
struct game_capture {int cx; int cy; int pitch; int /*<<< orphan*/ ** texture_buffers; } ;
typedef  int /*<<< orphan*/  __m128i ;

/* Variables and functions */
 int /*<<< orphan*/  _mm_add_epi32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_and_si128 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_load_si128 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _mm_or_si128 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_set1_epi32 (int) ; 
 int /*<<< orphan*/  _mm_setzero_si128 () ; 
 int /*<<< orphan*/  _mm_slli_epi32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _mm_store_si128 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_unpackhi_epi16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_unpacklo_epi16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void copy_b5g6r5_tex(struct game_capture *gc, int cur_texture,
			    uint8_t *data, uint32_t pitch)
{
	uint8_t *input = gc->texture_buffers[cur_texture];
	uint32_t gc_cx = gc->cx;
	uint32_t gc_cy = gc->cy;
	uint32_t gc_pitch = gc->pitch;

	for (uint32_t y = 0; y < gc_cy; y++) {
		uint8_t *row = input + (gc_pitch * y);
		uint8_t *out = data + (pitch * y);

		for (uint32_t x = 0; x < gc_cx; x += 8) {
			__m128i pixels_blue, pixels_green, pixels_red;
			__m128i pixels_result;
			__m128i *pixels_dest;

			__m128i *pixels_src =
				(__m128i *)(row + x * sizeof(uint16_t));
			__m128i pixels = _mm_load_si128(pixels_src);

			__m128i zero = _mm_setzero_si128();
			__m128i pixels_low = _mm_unpacklo_epi16(pixels, zero);
			__m128i pixels_high = _mm_unpackhi_epi16(pixels, zero);

			__m128i blue_channel_mask = _mm_set1_epi32(0x0000001F);
			__m128i blue_offset = _mm_set1_epi32(0x00000003);
			__m128i green_channel_mask = _mm_set1_epi32(0x000007E0);
			__m128i green_offset = _mm_set1_epi32(0x00000008);
			__m128i red_channel_mask = _mm_set1_epi32(0x0000F800);
			__m128i red_offset = _mm_set1_epi32(0x00000300);

			pixels_blue =
				_mm_and_si128(pixels_low, blue_channel_mask);
			pixels_blue = _mm_slli_epi32(pixels_blue, 3);
			pixels_blue = _mm_add_epi32(pixels_blue, blue_offset);

			pixels_green =
				_mm_and_si128(pixels_low, green_channel_mask);
			pixels_green =
				_mm_add_epi32(pixels_green, green_offset);
			pixels_green = _mm_slli_epi32(pixels_green, 5);

			pixels_red =
				_mm_and_si128(pixels_low, red_channel_mask);
			pixels_red = _mm_add_epi32(pixels_red, red_offset);
			pixels_red = _mm_slli_epi32(pixels_red, 8);

			pixels_result = _mm_set1_epi32(0xFF000000);
			pixels_result =
				_mm_or_si128(pixels_result, pixels_blue);
			pixels_result =
				_mm_or_si128(pixels_result, pixels_green);
			pixels_result = _mm_or_si128(pixels_result, pixels_red);

			pixels_dest = (__m128i *)(out + x * sizeof(uint32_t));
			_mm_store_si128(pixels_dest, pixels_result);

			pixels_blue =
				_mm_and_si128(pixels_high, blue_channel_mask);
			pixels_blue = _mm_slli_epi32(pixels_blue, 3);
			pixels_blue = _mm_add_epi32(pixels_blue, blue_offset);

			pixels_green =
				_mm_and_si128(pixels_high, green_channel_mask);
			pixels_green =
				_mm_add_epi32(pixels_green, green_offset);
			pixels_green = _mm_slli_epi32(pixels_green, 5);

			pixels_red =
				_mm_and_si128(pixels_high, red_channel_mask);
			pixels_red = _mm_add_epi32(pixels_red, red_offset);
			pixels_red = _mm_slli_epi32(pixels_red, 8);

			pixels_result = _mm_set1_epi32(0xFF000000);
			pixels_result =
				_mm_or_si128(pixels_result, pixels_blue);
			pixels_result =
				_mm_or_si128(pixels_result, pixels_green);
			pixels_result = _mm_or_si128(pixels_result, pixels_red);

			pixels_dest =
				(__m128i *)(out + (x + 4) * sizeof(uint32_t));
			_mm_store_si128(pixels_dest, pixels_result);
		}
	}
}