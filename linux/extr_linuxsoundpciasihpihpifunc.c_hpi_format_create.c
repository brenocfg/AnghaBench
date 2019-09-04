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
typedef  long u32 ;
typedef  int u16 ;
struct hpi_msg_format {int channels; int format; long sample_rate; long bit_rate; long attributes; } ;
struct hpi_format {int dummy; } ;

/* Variables and functions */
 int HPI_ERROR_INCOMPATIBLE_SAMPLERATE ; 
 int HPI_ERROR_INVALID_CHANNELS ; 
 int HPI_ERROR_INVALID_FORMAT ; 
#define  HPI_FORMAT_AA_TAGIT1_HITS 143 
#define  HPI_FORMAT_AA_TAGIT1_HITS_EX1 142 
#define  HPI_FORMAT_AA_TAGIT1_INSERTS 141 
#define  HPI_FORMAT_DOLBY_AC2 140 
#define  HPI_FORMAT_MPEG_L1 139 
#define  HPI_FORMAT_MPEG_L2 138 
#define  HPI_FORMAT_MPEG_L3 137 
#define  HPI_FORMAT_OEM1 136 
#define  HPI_FORMAT_OEM2 135 
#define  HPI_FORMAT_PCM16_BIGENDIAN 134 
#define  HPI_FORMAT_PCM16_SIGNED 133 
#define  HPI_FORMAT_PCM24_SIGNED 132 
#define  HPI_FORMAT_PCM32_FLOAT 131 
#define  HPI_FORMAT_PCM32_SIGNED 130 
#define  HPI_FORMAT_PCM8_UNSIGNED 129 
#define  HPI_FORMAT_RAW_BITSTREAM 128 
 long HPI_MPEG_MODE_DEFAULT ; 
 long HPI_MPEG_MODE_DUALCHANNEL ; 
 int /*<<< orphan*/  hpi_msg_to_format (struct hpi_format*,struct hpi_msg_format*) ; 

u16 hpi_format_create(struct hpi_format *p_format, u16 channels, u16 format,
	u32 sample_rate, u32 bit_rate, u32 attributes)
{
	u16 err = 0;
	struct hpi_msg_format fmt;

	switch (channels) {
	case 1:
	case 2:
	case 4:
	case 6:
	case 8:
	case 16:
		break;
	default:
		err = HPI_ERROR_INVALID_CHANNELS;
		return err;
	}
	fmt.channels = channels;

	switch (format) {
	case HPI_FORMAT_PCM16_SIGNED:
	case HPI_FORMAT_PCM24_SIGNED:
	case HPI_FORMAT_PCM32_SIGNED:
	case HPI_FORMAT_PCM32_FLOAT:
	case HPI_FORMAT_PCM16_BIGENDIAN:
	case HPI_FORMAT_PCM8_UNSIGNED:
	case HPI_FORMAT_MPEG_L1:
	case HPI_FORMAT_MPEG_L2:
	case HPI_FORMAT_MPEG_L3:
	case HPI_FORMAT_DOLBY_AC2:
	case HPI_FORMAT_AA_TAGIT1_HITS:
	case HPI_FORMAT_AA_TAGIT1_INSERTS:
	case HPI_FORMAT_RAW_BITSTREAM:
	case HPI_FORMAT_AA_TAGIT1_HITS_EX1:
	case HPI_FORMAT_OEM1:
	case HPI_FORMAT_OEM2:
		break;
	default:
		err = HPI_ERROR_INVALID_FORMAT;
		return err;
	}
	fmt.format = format;

	if (sample_rate < 8000L) {
		err = HPI_ERROR_INCOMPATIBLE_SAMPLERATE;
		sample_rate = 8000L;
	}
	if (sample_rate > 200000L) {
		err = HPI_ERROR_INCOMPATIBLE_SAMPLERATE;
		sample_rate = 200000L;
	}
	fmt.sample_rate = sample_rate;

	switch (format) {
	case HPI_FORMAT_MPEG_L1:
	case HPI_FORMAT_MPEG_L2:
	case HPI_FORMAT_MPEG_L3:
		fmt.bit_rate = bit_rate;
		break;
	case HPI_FORMAT_PCM16_SIGNED:
	case HPI_FORMAT_PCM16_BIGENDIAN:
		fmt.bit_rate = channels * sample_rate * 2;
		break;
	case HPI_FORMAT_PCM32_SIGNED:
	case HPI_FORMAT_PCM32_FLOAT:
		fmt.bit_rate = channels * sample_rate * 4;
		break;
	case HPI_FORMAT_PCM8_UNSIGNED:
		fmt.bit_rate = channels * sample_rate;
		break;
	default:
		fmt.bit_rate = 0;
	}

	switch (format) {
	case HPI_FORMAT_MPEG_L2:
		if ((channels == 1)
			&& (attributes != HPI_MPEG_MODE_DEFAULT)) {
			attributes = HPI_MPEG_MODE_DEFAULT;
			err = HPI_ERROR_INVALID_FORMAT;
		} else if (attributes > HPI_MPEG_MODE_DUALCHANNEL) {
			attributes = HPI_MPEG_MODE_DEFAULT;
			err = HPI_ERROR_INVALID_FORMAT;
		}
		fmt.attributes = attributes;
		break;
	default:
		fmt.attributes = attributes;
	}

	hpi_msg_to_format(p_format, &fmt);
	return err;
}