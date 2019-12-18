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
struct snd_soc_card {int /*<<< orphan*/  (* remove ) (struct snd_soc_card*) ;int /*<<< orphan*/  dapm; int /*<<< orphan*/ * snd_card; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_card_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_dapm_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  soc_cleanup_card_debugfs (struct snd_soc_card*) ; 
 int /*<<< orphan*/  soc_remove_aux_devices (struct snd_soc_card*) ; 
 int /*<<< orphan*/  soc_remove_dai_links (struct snd_soc_card*) ; 
 int /*<<< orphan*/  soc_remove_pcm_runtimes (struct snd_soc_card*) ; 
 int /*<<< orphan*/  soc_unbind_aux_dev (struct snd_soc_card*) ; 
 int /*<<< orphan*/  stub1 (struct snd_soc_card*) ; 

__attribute__((used)) static void soc_cleanup_card_resources(struct snd_soc_card *card)
{
	/* free the ALSA card at first; this syncs with pending operations */
	if (card->snd_card) {
		snd_card_free(card->snd_card);
		card->snd_card = NULL;
	}

	/* remove and free each DAI */
	soc_remove_dai_links(card);
	soc_remove_pcm_runtimes(card);

	/* remove auxiliary devices */
	soc_remove_aux_devices(card);
	soc_unbind_aux_dev(card);

	snd_soc_dapm_free(&card->dapm);
	soc_cleanup_card_debugfs(card);

	/* remove the card */
	if (card->remove)
		card->remove(card);
}