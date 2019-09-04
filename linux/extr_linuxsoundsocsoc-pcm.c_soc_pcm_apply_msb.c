#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {int num_codecs; struct snd_soc_dai** codec_dais; struct snd_soc_dai* cpu_dai; } ;
struct snd_soc_dai {TYPE_3__* driver; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_soc_pcm_runtime* private_data; } ;
struct TYPE_5__ {scalar_t__ sig_bits; } ;
struct TYPE_4__ {scalar_t__ sig_bits; } ;
struct TYPE_6__ {TYPE_2__ capture; TYPE_1__ playback; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 unsigned int max (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  soc_pcm_set_msb (struct snd_pcm_substream*,unsigned int) ; 

__attribute__((used)) static void soc_pcm_apply_msb(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
	struct snd_soc_dai *codec_dai;
	int i;
	unsigned int bits = 0, cpu_bits;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		for (i = 0; i < rtd->num_codecs; i++) {
			codec_dai = rtd->codec_dais[i];
			if (codec_dai->driver->playback.sig_bits == 0) {
				bits = 0;
				break;
			}
			bits = max(codec_dai->driver->playback.sig_bits, bits);
		}
		cpu_bits = cpu_dai->driver->playback.sig_bits;
	} else {
		for (i = 0; i < rtd->num_codecs; i++) {
			codec_dai = rtd->codec_dais[i];
			if (codec_dai->driver->capture.sig_bits == 0) {
				bits = 0;
				break;
			}
			bits = max(codec_dai->driver->capture.sig_bits, bits);
		}
		cpu_bits = cpu_dai->driver->capture.sig_bits;
	}

	soc_pcm_set_msb(substream, bits);
	soc_pcm_set_msb(substream, cpu_bits);
}