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
struct snd_soc_card {int instantiated; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_dapm_shutdown (struct snd_soc_card*) ; 
 int /*<<< orphan*/  snd_soc_flush_all_delayed_work (struct snd_soc_card*) ; 
 int /*<<< orphan*/  soc_cleanup_card_resources (struct snd_soc_card*) ; 
 int /*<<< orphan*/  soc_remove_link_components (struct snd_soc_card*) ; 
 int /*<<< orphan*/  unbind_card_list ; 

__attribute__((used)) static void snd_soc_unbind_card(struct snd_soc_card *card, bool unregister)
{
	if (card->instantiated) {
		card->instantiated = false;
		snd_soc_dapm_shutdown(card);
		snd_soc_flush_all_delayed_work(card);

		/* remove all components used by DAI links on this card */
		soc_remove_link_components(card);

		soc_cleanup_card_resources(card);
		if (!unregister)
			list_add(&card->list, &unbind_card_list);
	} else {
		if (unregister)
			list_del(&card->list);
	}
}