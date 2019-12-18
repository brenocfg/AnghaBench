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
struct snd_trident_voice {int dummy; } ;
struct snd_trident_pcm_mixer {int /*<<< orphan*/  cvol; int /*<<< orphan*/  rvol; int /*<<< orphan*/  pan; int /*<<< orphan*/  vol; struct snd_trident_voice* voice; } ;
struct snd_trident {struct snd_trident_pcm_mixer* pcm_mixer; } ;
struct snd_pcm_substream {size_t number; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  T4D_DEFAULT_PCM_CVOL ; 
 int /*<<< orphan*/  T4D_DEFAULT_PCM_PAN ; 
 int /*<<< orphan*/  T4D_DEFAULT_PCM_RVOL ; 
 int /*<<< orphan*/  T4D_DEFAULT_PCM_VOL ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_trident_notify_pcm_change (struct snd_trident*,struct snd_trident_pcm_mixer*,size_t,int) ; 

__attribute__((used)) static int snd_trident_pcm_mixer_build(struct snd_trident *trident,
				       struct snd_trident_voice *voice,
				       struct snd_pcm_substream *substream)
{
	struct snd_trident_pcm_mixer *tmix;

	if (snd_BUG_ON(!trident || !voice || !substream))
		return -EINVAL;
	tmix = &trident->pcm_mixer[substream->number];
	tmix->voice = voice;
	tmix->vol = T4D_DEFAULT_PCM_VOL;
	tmix->pan = T4D_DEFAULT_PCM_PAN;
	tmix->rvol = T4D_DEFAULT_PCM_RVOL;
	tmix->cvol = T4D_DEFAULT_PCM_CVOL;
	snd_trident_notify_pcm_change(trident, tmix, substream->number, 1);
	return 0;
}