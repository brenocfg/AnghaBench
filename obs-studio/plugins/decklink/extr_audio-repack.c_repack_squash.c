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
struct audio_repack {int extra_dst_size; scalar_t__ packet_buffer; } ;
typedef  int /*<<< orphan*/  __m128i ;

/* Variables and functions */
 int /*<<< orphan*/  _mm_load_si128 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_storeu_si128 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ check_buffer (struct audio_repack*,int) ; 

int repack_squash(struct audio_repack *repack, const uint8_t *bsrc,
		  uint32_t frame_count)
{
	if (check_buffer(repack, frame_count) < 0)
		return -1;

	int squash = repack->extra_dst_size;
	const __m128i *src = (__m128i *)bsrc;
	const __m128i *esrc = src + frame_count;
	uint16_t *dst = (uint16_t *)repack->packet_buffer;

	/*  Audio needs squashing in order to avoid resampling issues.
	 * The condition checks for 7.1 audio for which no squash is needed.
	 */
	if (squash > 0) {
		while (src != esrc) {
			__m128i target = _mm_load_si128(src++);
			_mm_storeu_si128((__m128i *)dst, target);
			dst += 8 - squash;
		}
	}

	return 0;
}