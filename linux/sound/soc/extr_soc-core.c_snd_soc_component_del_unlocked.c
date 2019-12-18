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
struct snd_soc_component {int /*<<< orphan*/  list; struct snd_soc_card* card; } ;
struct snd_soc_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_unbind_card (struct snd_soc_card*,int) ; 

__attribute__((used)) static void snd_soc_component_del_unlocked(struct snd_soc_component *component)
{
	struct snd_soc_card *card = component->card;

	if (card)
		snd_soc_unbind_card(card, false);

	list_del(&component->list);
}