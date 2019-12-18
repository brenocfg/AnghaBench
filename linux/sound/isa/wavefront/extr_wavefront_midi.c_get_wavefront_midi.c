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
struct snd_rawmidi_substream {TYPE_1__* rmidi; } ;
struct snd_card {TYPE_3__* private_data; } ;
typedef  int /*<<< orphan*/  snd_wavefront_midi_t ;
struct TYPE_5__ {int /*<<< orphan*/  midi; } ;
struct TYPE_6__ {TYPE_2__ wavefront; } ;
typedef  TYPE_3__ snd_wavefront_card_t ;
struct TYPE_4__ {struct snd_card* card; } ;

/* Variables and functions */

__attribute__((used)) static snd_wavefront_midi_t *
get_wavefront_midi (struct snd_rawmidi_substream *substream)

{
	struct snd_card *card;
	snd_wavefront_card_t *acard;

	if (substream == NULL || substream->rmidi == NULL) 
	        return NULL;

	card = substream->rmidi->card;

	if (card == NULL) 
	        return NULL;

	if (card->private_data == NULL) 
 	        return NULL;

	acard = card->private_data;

	return &acard->wavefront.midi;
}