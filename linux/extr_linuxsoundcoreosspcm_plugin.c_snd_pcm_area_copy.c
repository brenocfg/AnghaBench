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
struct snd_pcm_channel_area {char* addr; size_t first; size_t step; } ;
typedef  int /*<<< orphan*/  snd_pcm_format_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int snd_pcm_area_silence (struct snd_pcm_channel_area const*,size_t,size_t,int /*<<< orphan*/ ) ; 
 int snd_pcm_format_physical_width (int /*<<< orphan*/ ) ; 

int snd_pcm_area_copy(const struct snd_pcm_channel_area *src_area, size_t src_offset,
		      const struct snd_pcm_channel_area *dst_area, size_t dst_offset,
		      size_t samples, snd_pcm_format_t format)
{
	/* FIXME: sub byte resolution and odd dst_offset */
	char *src, *dst;
	int width;
	int src_step, dst_step;
	src = src_area->addr + (src_area->first + src_area->step * src_offset) / 8;
	if (!src_area->addr)
		return snd_pcm_area_silence(dst_area, dst_offset, samples, format);
	dst = dst_area->addr + (dst_area->first + dst_area->step * dst_offset) / 8;
	if (!dst_area->addr)
		return 0;
	width = snd_pcm_format_physical_width(format);
	if (width <= 0)
		return -EINVAL;
	if (src_area->step == (unsigned int) width &&
	    dst_area->step == (unsigned int) width && width >= 8) {
		size_t bytes = samples * width / 8;
		memcpy(dst, src, bytes);
		return 0;
	}
	src_step = src_area->step / 8;
	dst_step = dst_area->step / 8;
	if (width == 4) {
		/* Ima ADPCM */
		int srcbit = src_area->first % 8;
		int srcbit_step = src_area->step % 8;
		int dstbit = dst_area->first % 8;
		int dstbit_step = dst_area->step % 8;
		while (samples-- > 0) {
			unsigned char srcval;
			if (srcbit)
				srcval = *src & 0x0f;
			else
				srcval = (*src & 0xf0) >> 4;
			if (dstbit)
				*dst = (*dst & 0xf0) | srcval;
			else
				*dst = (*dst & 0x0f) | (srcval << 4);
			src += src_step;
			srcbit += srcbit_step;
			if (srcbit == 8) {
				src++;
				srcbit = 0;
			}
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
			memcpy(dst, src, width);
			src += src_step;
			dst += dst_step;
		}
	}
	return 0;
}