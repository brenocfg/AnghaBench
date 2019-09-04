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
typedef  enum audio_format { ____Placeholder_audio_format } audio_format ;

/* Variables and functions */
#define  AUDIO_FORMAT_16BIT 136 
#define  AUDIO_FORMAT_16BIT_PLANAR 135 
#define  AUDIO_FORMAT_32BIT 134 
#define  AUDIO_FORMAT_32BIT_PLANAR 133 
#define  AUDIO_FORMAT_FLOAT 132 
#define  AUDIO_FORMAT_FLOAT_PLANAR 131 
#define  AUDIO_FORMAT_U8BIT 130 
#define  AUDIO_FORMAT_U8BIT_PLANAR 129 
#define  AUDIO_FORMAT_UNKNOWN 128 

__attribute__((used)) static inline size_t get_audio_bytes_per_channel(enum audio_format format)
{
	switch (format) {
	case AUDIO_FORMAT_U8BIT:
	case AUDIO_FORMAT_U8BIT_PLANAR:
		return 1;

	case AUDIO_FORMAT_16BIT:
	case AUDIO_FORMAT_16BIT_PLANAR:
		return 2;

	case AUDIO_FORMAT_FLOAT:
	case AUDIO_FORMAT_FLOAT_PLANAR:
	case AUDIO_FORMAT_32BIT:
	case AUDIO_FORMAT_32BIT_PLANAR:
		return 4;

	case AUDIO_FORMAT_UNKNOWN:
		return 0;
	}

	return 0;
}