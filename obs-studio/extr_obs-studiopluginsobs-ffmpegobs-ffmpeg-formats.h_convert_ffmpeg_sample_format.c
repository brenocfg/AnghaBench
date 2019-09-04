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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  enum audio_format { ____Placeholder_audio_format } audio_format ;
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;

/* Variables and functions */
 int AUDIO_FORMAT_16BIT ; 
 int AUDIO_FORMAT_16BIT_PLANAR ; 
 int AUDIO_FORMAT_32BIT ; 
 int AUDIO_FORMAT_32BIT_PLANAR ; 
 int AUDIO_FORMAT_FLOAT ; 
 int AUDIO_FORMAT_FLOAT_PLANAR ; 
 int AUDIO_FORMAT_U8BIT ; 
 int AUDIO_FORMAT_U8BIT_PLANAR ; 
#define  AV_SAMPLE_FMT_FLT 135 
#define  AV_SAMPLE_FMT_FLTP 134 
#define  AV_SAMPLE_FMT_S16 133 
#define  AV_SAMPLE_FMT_S16P 132 
#define  AV_SAMPLE_FMT_S32 131 
#define  AV_SAMPLE_FMT_S32P 130 
#define  AV_SAMPLE_FMT_U8 129 
#define  AV_SAMPLE_FMT_U8P 128 

__attribute__((used)) static inline enum audio_format convert_ffmpeg_sample_format(
		enum AVSampleFormat format)
{
	switch ((uint32_t)format) {
	case AV_SAMPLE_FMT_U8:   return AUDIO_FORMAT_U8BIT;
	case AV_SAMPLE_FMT_S16:  return AUDIO_FORMAT_16BIT;
	case AV_SAMPLE_FMT_S32:  return AUDIO_FORMAT_32BIT;
	case AV_SAMPLE_FMT_FLT:  return AUDIO_FORMAT_FLOAT;
	case AV_SAMPLE_FMT_U8P:  return AUDIO_FORMAT_U8BIT_PLANAR;
	case AV_SAMPLE_FMT_S16P: return AUDIO_FORMAT_16BIT_PLANAR;
	case AV_SAMPLE_FMT_S32P: return AUDIO_FORMAT_32BIT_PLANAR;
	case AV_SAMPLE_FMT_FLTP: return AUDIO_FORMAT_FLOAT_PLANAR;
	}

	/* shouldn't get here */
	return AUDIO_FORMAT_16BIT;
}