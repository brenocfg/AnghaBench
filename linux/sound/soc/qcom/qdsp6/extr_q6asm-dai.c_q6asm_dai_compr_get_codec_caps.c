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
struct snd_compr_stream {int dummy; } ;
struct snd_compr_codec_caps {int codec; } ;

/* Variables and functions */
#define  SND_AUDIOCODEC_MP3 128 
 struct snd_compr_codec_caps q6asm_compr_caps ; 

__attribute__((used)) static int q6asm_dai_compr_get_codec_caps(struct snd_compr_stream *stream,
					  struct snd_compr_codec_caps *codec)
{
	switch (codec->codec) {
	case SND_AUDIOCODEC_MP3:
		*codec = q6asm_compr_caps;
		break;
	default:
		break;
	}

	return 0;
}