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
struct snd_compr_codec_caps {scalar_t__ codec; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SND_AUDIOCODEC_AAC ; 
 scalar_t__ SND_AUDIOCODEC_MP3 ; 
 struct snd_compr_codec_caps caps_aac ; 
 struct snd_compr_codec_caps caps_mp3 ; 

__attribute__((used)) static int sst_cdev_codec_caps(struct snd_compr_codec_caps *codec)
{
	if (codec->codec == SND_AUDIOCODEC_MP3)
		*codec = caps_mp3;
	else if (codec->codec == SND_AUDIOCODEC_AAC)
		*codec = caps_aac;
	else
		return -EINVAL;

	return 0;
}