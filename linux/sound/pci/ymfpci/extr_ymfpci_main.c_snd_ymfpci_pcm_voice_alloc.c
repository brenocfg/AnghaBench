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
struct snd_ymfpci_pcm {TYPE_2__** voices; TYPE_1__* chip; } ;
struct TYPE_6__ {int number; struct snd_ymfpci_pcm* ypcm; int /*<<< orphan*/  interrupt; } ;
struct TYPE_5__ {TYPE_2__* voices; } ;

/* Variables and functions */
 int /*<<< orphan*/  YMFPCI_PCM ; 
 int /*<<< orphan*/  snd_ymfpci_pcm_interrupt ; 
 int snd_ymfpci_voice_alloc (TYPE_1__*,int /*<<< orphan*/ ,int,TYPE_2__**) ; 
 int /*<<< orphan*/  snd_ymfpci_voice_free (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static int snd_ymfpci_pcm_voice_alloc(struct snd_ymfpci_pcm *ypcm, int voices)
{
	int err;

	if (ypcm->voices[1] != NULL && voices < 2) {
		snd_ymfpci_voice_free(ypcm->chip, ypcm->voices[1]);
		ypcm->voices[1] = NULL;
	}
	if (voices == 1 && ypcm->voices[0] != NULL)
		return 0;		/* already allocated */
	if (voices == 2 && ypcm->voices[0] != NULL && ypcm->voices[1] != NULL)
		return 0;		/* already allocated */
	if (voices > 1) {
		if (ypcm->voices[0] != NULL && ypcm->voices[1] == NULL) {
			snd_ymfpci_voice_free(ypcm->chip, ypcm->voices[0]);
			ypcm->voices[0] = NULL;
		}		
	}
	err = snd_ymfpci_voice_alloc(ypcm->chip, YMFPCI_PCM, voices > 1, &ypcm->voices[0]);
	if (err < 0)
		return err;
	ypcm->voices[0]->ypcm = ypcm;
	ypcm->voices[0]->interrupt = snd_ymfpci_pcm_interrupt;
	if (voices > 1) {
		ypcm->voices[1] = &ypcm->chip->voices[ypcm->voices[0]->number + 1];
		ypcm->voices[1]->ypcm = ypcm;
	}
	return 0;
}