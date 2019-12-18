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
struct hda_codec {int dummy; } ;
struct cea_sad {int max_bitrate; int format; void* profile; scalar_t__ sample_bits; void* channels; int /*<<< orphan*/  rates; } ;

/* Variables and functions */
#define  AUDIO_CODING_TYPE_AACLC 143 
#define  AUDIO_CODING_TYPE_AC3 142 
#define  AUDIO_CODING_TYPE_ATRAC 141 
#define  AUDIO_CODING_TYPE_DST 140 
#define  AUDIO_CODING_TYPE_DTS 139 
#define  AUDIO_CODING_TYPE_DTS_HD 138 
#define  AUDIO_CODING_TYPE_EAC3 137 
 int AUDIO_CODING_TYPE_HE_AAC ; 
#define  AUDIO_CODING_TYPE_LPCM 136 
#define  AUDIO_CODING_TYPE_MLP 135 
#define  AUDIO_CODING_TYPE_MP3 134 
#define  AUDIO_CODING_TYPE_MPEG1 133 
#define  AUDIO_CODING_TYPE_MPEG2 132 
#define  AUDIO_CODING_TYPE_REF_CXT 131 
#define  AUDIO_CODING_TYPE_REF_STREAM_HEADER 130 
#define  AUDIO_CODING_TYPE_SACD 129 
#define  AUDIO_CODING_TYPE_WMAPRO 128 
 int AUDIO_CODING_XTYPE_FIRST_RESERVED ; 
 int AUDIO_CODING_XTYPE_HE_AAC ; 
 int AUDIO_CODING_XTYPE_HE_REF_CT ; 
 void* GRAB_BITS (unsigned char const*,int,int,int) ; 
 scalar_t__* cea_sample_sizes ; 
 int /*<<< orphan*/ * cea_sampling_frequencies ; 
 int /*<<< orphan*/  codec_info (struct hda_codec*,char*,...) ; 

__attribute__((used)) static void hdmi_update_short_audio_desc(struct hda_codec *codec,
					 struct cea_sad *a,
					 const unsigned char *buf)
{
	int i;
	int val;

	val = GRAB_BITS(buf, 1, 0, 7);
	a->rates = 0;
	for (i = 0; i < 7; i++)
		if (val & (1 << i))
			a->rates |= cea_sampling_frequencies[i + 1];

	a->channels = GRAB_BITS(buf, 0, 0, 3);
	a->channels++;

	a->sample_bits = 0;
	a->max_bitrate = 0;

	a->format = GRAB_BITS(buf, 0, 3, 4);
	switch (a->format) {
	case AUDIO_CODING_TYPE_REF_STREAM_HEADER:
		codec_info(codec, "HDMI: audio coding type 0 not expected\n");
		break;

	case AUDIO_CODING_TYPE_LPCM:
		val = GRAB_BITS(buf, 2, 0, 3);
		for (i = 0; i < 3; i++)
			if (val & (1 << i))
				a->sample_bits |= cea_sample_sizes[i + 1];
		break;

	case AUDIO_CODING_TYPE_AC3:
	case AUDIO_CODING_TYPE_MPEG1:
	case AUDIO_CODING_TYPE_MP3:
	case AUDIO_CODING_TYPE_MPEG2:
	case AUDIO_CODING_TYPE_AACLC:
	case AUDIO_CODING_TYPE_DTS:
	case AUDIO_CODING_TYPE_ATRAC:
		a->max_bitrate = GRAB_BITS(buf, 2, 0, 8);
		a->max_bitrate *= 8000;
		break;

	case AUDIO_CODING_TYPE_SACD:
		break;

	case AUDIO_CODING_TYPE_EAC3:
		break;

	case AUDIO_CODING_TYPE_DTS_HD:
		break;

	case AUDIO_CODING_TYPE_MLP:
		break;

	case AUDIO_CODING_TYPE_DST:
		break;

	case AUDIO_CODING_TYPE_WMAPRO:
		a->profile = GRAB_BITS(buf, 2, 0, 3);
		break;

	case AUDIO_CODING_TYPE_REF_CXT:
		a->format = GRAB_BITS(buf, 2, 3, 5);
		if (a->format == AUDIO_CODING_XTYPE_HE_REF_CT ||
		    a->format >= AUDIO_CODING_XTYPE_FIRST_RESERVED) {
			codec_info(codec,
				   "HDMI: audio coding xtype %d not expected\n",
				   a->format);
			a->format = 0;
		} else
			a->format += AUDIO_CODING_TYPE_HE_AAC -
				     AUDIO_CODING_XTYPE_HE_AAC;
		break;
	}
}