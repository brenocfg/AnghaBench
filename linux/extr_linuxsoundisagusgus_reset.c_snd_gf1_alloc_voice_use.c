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
struct snd_gus_voice {int use; int pcm; int synth; int client; int port; int midi; } ;
struct TYPE_2__ {int /*<<< orphan*/  pcm_alloc_voices; } ;
struct snd_gus_card {TYPE_1__ gf1; } ;

/* Variables and functions */
#define  SNDRV_GF1_VOICE_TYPE_MIDI 130 
#define  SNDRV_GF1_VOICE_TYPE_PCM 129 
#define  SNDRV_GF1_VOICE_TYPE_SYNTH 128 

__attribute__((used)) static void snd_gf1_alloc_voice_use(struct snd_gus_card * gus, 
				    struct snd_gus_voice * pvoice,
				    int type, int client, int port)
{
	pvoice->use = 1;
	switch (type) {
	case SNDRV_GF1_VOICE_TYPE_PCM:
		gus->gf1.pcm_alloc_voices++;
		pvoice->pcm = 1;
		break;
	case SNDRV_GF1_VOICE_TYPE_SYNTH:
		pvoice->synth = 1;
		pvoice->client = client;
		pvoice->port = port;
		break;
	case SNDRV_GF1_VOICE_TYPE_MIDI:
		pvoice->midi = 1;
		pvoice->client = client;
		pvoice->port = port;
		break;
	}
}