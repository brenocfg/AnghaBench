#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct snd_uac_chip* rbuf; struct snd_uac_chip* ureq; } ;
struct TYPE_3__ {struct snd_uac_chip* rbuf; struct snd_uac_chip* ureq; } ;
struct snd_uac_chip {TYPE_2__ c_prm; TYPE_1__ p_prm; struct snd_card* card; } ;
struct snd_card {int dummy; } ;
struct g_audio {struct snd_uac_chip* uac; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_uac_chip*) ; 
 int /*<<< orphan*/  snd_card_free (struct snd_card*) ; 

void g_audio_cleanup(struct g_audio *g_audio)
{
	struct snd_uac_chip *uac;
	struct snd_card *card;

	if (!g_audio || !g_audio->uac)
		return;

	uac = g_audio->uac;
	card = uac->card;
	if (card)
		snd_card_free(card);

	kfree(uac->p_prm.ureq);
	kfree(uac->c_prm.ureq);
	kfree(uac->p_prm.rbuf);
	kfree(uac->c_prm.rbuf);
	kfree(uac);
}