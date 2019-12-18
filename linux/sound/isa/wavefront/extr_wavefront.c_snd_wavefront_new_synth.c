#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ioctl; int /*<<< orphan*/  release; int /*<<< orphan*/  open; } ;
struct snd_hwdep {TYPE_1__ ops; int /*<<< orphan*/  name; } ;
struct snd_card {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  wavefront; } ;
typedef  TYPE_2__ snd_wavefront_card_t ;

/* Variables and functions */
 scalar_t__ snd_hwdep_new (struct snd_card*,char*,int,struct snd_hwdep**) ; 
 scalar_t__ snd_wavefront_detect (TYPE_2__*) ; 
 scalar_t__ snd_wavefront_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_wavefront_synth_ioctl ; 
 int /*<<< orphan*/  snd_wavefront_synth_open ; 
 int /*<<< orphan*/  snd_wavefront_synth_release ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct snd_hwdep *snd_wavefront_new_synth(struct snd_card *card,
						 int hw_dev,
						 snd_wavefront_card_t *acard)
{
	struct snd_hwdep *wavefront_synth;

	if (snd_wavefront_detect (acard) < 0) {
		return NULL;
	}

	if (snd_wavefront_start (&acard->wavefront) < 0) {
		return NULL;
	}

	if (snd_hwdep_new(card, "WaveFront", hw_dev, &wavefront_synth) < 0)
		return NULL;
	strcpy (wavefront_synth->name, 
		"WaveFront (ICS2115) wavetable synthesizer");
	wavefront_synth->ops.open = snd_wavefront_synth_open;
	wavefront_synth->ops.release = snd_wavefront_synth_release;
	wavefront_synth->ops.ioctl = snd_wavefront_synth_ioctl;

	return wavefront_synth;
}