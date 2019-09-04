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
struct snd_soc_jack {int status; } ;
struct nau8824 {scalar_t__ irq; struct snd_soc_jack* jack; } ;

/* Variables and functions */
 int FALSE ; 
 int SND_JACK_HEADPHONE ; 

__attribute__((used)) static bool nau8824_is_jack_inserted(struct nau8824 *nau8824)
{
	struct snd_soc_jack *jack = nau8824->jack;
	bool insert = FALSE;

	if (nau8824->irq && jack)
		insert = jack->status & SND_JACK_HEADPHONE;

	return insert;
}