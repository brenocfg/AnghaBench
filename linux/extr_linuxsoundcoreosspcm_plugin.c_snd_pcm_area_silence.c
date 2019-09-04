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
struct snd_pcm_channel_area {unsigned char* addr; size_t first; size_t step; } ;
typedef  int /*<<< orphan*/  snd_pcm_format_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 
 int snd_pcm_format_physical_width (int /*<<< orphan*/ ) ; 
 int snd_pcm_format_set_silence (int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 unsigned char* snd_pcm_format_silence_64 (int /*<<< orphan*/ ) ; 

int snd_pcm_area_silence(const struct snd_pcm_channel_area *dst_area, size_t dst_offset,
			 size_t samples, snd_pcm_format_t format)
{
	/* FIXME: sub byte resolution and odd dst_offset */
	unsigned char *dst;
	unsigned int dst_step;
	int width;
	const unsigned char *silence;
	if (!dst_area->addr)
		return 0;
	dst = dst_area->addr + (dst_area->first + dst_area->step * dst_offset) / 8;
	width = snd_pcm_format_physical_width(format);
	if (width <= 0)
		return -EINVAL;
	if (dst_area->step == (unsigned int) width && width >= 8)
		return snd_pcm_format_set_silence(format, dst, samples);
	silence = snd_pcm_format_silence_64(format);
	if (! silence)
		return -EINVAL;
	dst_step = dst_area->step / 8;
	if (width == 4) {
		/* Ima ADPCM */
		int dstbit = dst_area->first % 8;
		int dstbit_step = dst_area->step % 8;
		while (samples-- > 0) {
			if (dstbit)
				*dst &= 0xf0;
			else
				*dst &= 0x0f;
			dst += dst_step;
			dstbit += dstbit_step;
			if (dstbit == 8) {
				dst++;
				dstbit = 0;
			}
		}
	} else {
		width /= 8;
		while (samples-- > 0) {
			memcpy(dst, silence, width);
			dst += dst_step;
		}
	}
	return 0;
}