#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ type; } ;
struct snd_soc_dai_link {int /*<<< orphan*/  list; TYPE_1__ dobj; } ;
struct snd_soc_card {int /*<<< orphan*/  (* remove_dai_link ) (struct snd_soc_card*,struct snd_soc_dai_link*) ;int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ SND_SOC_DOBJ_DAI_LINK ; 
 int /*<<< orphan*/  client_mutex ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct snd_soc_card*,struct snd_soc_dai_link*) ; 

void snd_soc_remove_dai_link(struct snd_soc_card *card,
			     struct snd_soc_dai_link *dai_link)
{
	if (dai_link->dobj.type
	    && dai_link->dobj.type != SND_SOC_DOBJ_DAI_LINK) {
		dev_err(card->dev, "Invalid dai link type %d\n",
			dai_link->dobj.type);
		return;
	}

	lockdep_assert_held(&client_mutex);
	/*
	 * Notify the machine driver for extra destruction
	 * on the link created by topology.
	 */
	if (dai_link->dobj.type && card->remove_dai_link)
		card->remove_dai_link(card, dai_link);

	list_del(&dai_link->list);
}