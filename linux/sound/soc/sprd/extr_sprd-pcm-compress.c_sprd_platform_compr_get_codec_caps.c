#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_compr_stream {int dummy; } ;
struct snd_compr_codec_caps {int codec; int num_descriptors; TYPE_1__* descriptor; } ;
struct TYPE_2__ {int max_ch; int* bit_rate; int num_bitrates; int /*<<< orphan*/  formats; int /*<<< orphan*/  modes; int /*<<< orphan*/  profiles; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SND_AUDIOCHANMODE_MP3_STEREO ; 
#define  SND_AUDIOCODEC_AAC 129 
#define  SND_AUDIOCODEC_MP3 128 

__attribute__((used)) static int
sprd_platform_compr_get_codec_caps(struct snd_compr_stream *cstream,
				   struct snd_compr_codec_caps *codec)
{
	switch (codec->codec) {
	case SND_AUDIOCODEC_MP3:
		codec->num_descriptors = 2;
		codec->descriptor[0].max_ch = 2;
		codec->descriptor[0].bit_rate[0] = 320;
		codec->descriptor[0].bit_rate[1] = 128;
		codec->descriptor[0].num_bitrates = 2;
		codec->descriptor[0].profiles = 0;
		codec->descriptor[0].modes = SND_AUDIOCHANMODE_MP3_STEREO;
		codec->descriptor[0].formats = 0;
		break;

	case SND_AUDIOCODEC_AAC:
		codec->num_descriptors = 2;
		codec->descriptor[1].max_ch = 2;
		codec->descriptor[1].bit_rate[0] = 320;
		codec->descriptor[1].bit_rate[1] = 128;
		codec->descriptor[1].num_bitrates = 2;
		codec->descriptor[1].profiles = 0;
		codec->descriptor[1].modes = 0;
		codec->descriptor[1].formats = 0;
		break;

	default:
		return -EINVAL;
	}

	return 0;
}