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
struct snd_soc_card {int instantiated; int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_shutdown (struct snd_soc_card*) ; 
 int /*<<< orphan*/  soc_cleanup_card_resources (struct snd_soc_card*) ; 

int snd_soc_unregister_card(struct snd_soc_card *card)
{
	if (card->instantiated) {
		card->instantiated = false;
		snd_soc_dapm_shutdown(card);
		soc_cleanup_card_resources(card);
		dev_dbg(card->dev, "ASoC: Unregistered card '%s'\n", card->name);
	}

	return 0;
}