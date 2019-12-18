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
typedef  int u32 ;
typedef  long u16 ;
struct hpi_format {long channels; int format; long sample_rate; long bit_rate; } ;

/* Variables and functions */
 long HPI_ERROR_INVALID_FORMAT ; 
#define  HPI_FORMAT_DOLBY_AC2 137 
#define  HPI_FORMAT_MPEG_L1 136 
#define  HPI_FORMAT_MPEG_L2 135 
#define  HPI_FORMAT_MPEG_L3 134 
#define  HPI_FORMAT_PCM16_BIGENDIAN 133 
#define  HPI_FORMAT_PCM16_SIGNED 132 
#define  HPI_FORMAT_PCM24_SIGNED 131 
#define  HPI_FORMAT_PCM32_FLOAT 130 
#define  HPI_FORMAT_PCM32_SIGNED 129 
#define  HPI_FORMAT_PCM8_UNSIGNED 128 
 int roundup_pow_of_two (int) ; 

u16 hpi_stream_estimate_buffer_size(struct hpi_format *p_format,
	u32 host_polling_rate_in_milli_seconds, u32 *recommended_buffer_size)
{

	u32 bytes_per_second;
	u32 size;
	u16 channels;
	struct hpi_format *pF = p_format;

	channels = pF->channels;

	switch (pF->format) {
	case HPI_FORMAT_PCM16_BIGENDIAN:
	case HPI_FORMAT_PCM16_SIGNED:
		bytes_per_second = pF->sample_rate * 2L * channels;
		break;
	case HPI_FORMAT_PCM24_SIGNED:
		bytes_per_second = pF->sample_rate * 3L * channels;
		break;
	case HPI_FORMAT_PCM32_SIGNED:
	case HPI_FORMAT_PCM32_FLOAT:
		bytes_per_second = pF->sample_rate * 4L * channels;
		break;
	case HPI_FORMAT_PCM8_UNSIGNED:
		bytes_per_second = pF->sample_rate * 1L * channels;
		break;
	case HPI_FORMAT_MPEG_L1:
	case HPI_FORMAT_MPEG_L2:
	case HPI_FORMAT_MPEG_L3:
		bytes_per_second = pF->bit_rate / 8L;
		break;
	case HPI_FORMAT_DOLBY_AC2:

		bytes_per_second = 256000L / 8L;
		break;
	default:
		return HPI_ERROR_INVALID_FORMAT;
	}
	size = (bytes_per_second * host_polling_rate_in_milli_seconds * 2) /
		1000L;

	*recommended_buffer_size =
		roundup_pow_of_two(((size + 4095L) & ~4095L));
	return 0;
}