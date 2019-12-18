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
struct snd_soc_card {int /*<<< orphan*/  dai_link_list; int /*<<< orphan*/  (* add_dai_link ) (struct snd_soc_card*,struct snd_soc_dai_link*) ;int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SND_SOC_DOBJ_DAI_LINK ; 
 int /*<<< orphan*/  client_mutex ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct snd_soc_card*,struct snd_soc_dai_link*) ; 

int snd_soc_add_dai_link(struct snd_soc_card *card,
		struct snd_soc_dai_link *dai_link)
{
	if (dai_link->dobj.type
	    && dai_link->dobj.type != SND_SOC_DOBJ_DAI_LINK) {
		dev_err(card->dev, "Invalid dai link type %d\n",
			dai_link->dobj.type);
		return -EINVAL;
	}

	lockdep_assert_held(&client_mutex);
	/*
	 * Notify the machine driver for extra initialization
	 * on the link created by topology.
	 */
	if (dai_link->dobj.type && card->add_dai_link)
		card->add_dai_link(card, dai_link);

	/* see for_each_card_links */
	list_add_tail(&dai_link->list, &card->dai_link_list);

	return 0;
}