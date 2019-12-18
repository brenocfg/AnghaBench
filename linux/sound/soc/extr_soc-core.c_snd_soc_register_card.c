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
struct snd_soc_card {int /*<<< orphan*/  dpcm_lock; int /*<<< orphan*/  pcm_mutex; int /*<<< orphan*/  dapm_mutex; int /*<<< orphan*/  mutex; scalar_t__ instantiated; scalar_t__ num_rtd; int /*<<< orphan*/  dobj_list; int /*<<< orphan*/  dapm_dirty; int /*<<< orphan*/  rtd_list; int /*<<< orphan*/  dai_link_list; int /*<<< orphan*/  list; int /*<<< orphan*/  component_dev_list; int /*<<< orphan*/  aux_comp_list; int /*<<< orphan*/  dapm_list; int /*<<< orphan*/  paths; int /*<<< orphan*/  widgets; int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ ,struct snd_soc_card*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int snd_soc_bind_card (struct snd_soc_card*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int snd_soc_register_card(struct snd_soc_card *card)
{
	if (!card->name || !card->dev)
		return -EINVAL;

	dev_set_drvdata(card->dev, card);

	INIT_LIST_HEAD(&card->widgets);
	INIT_LIST_HEAD(&card->paths);
	INIT_LIST_HEAD(&card->dapm_list);
	INIT_LIST_HEAD(&card->aux_comp_list);
	INIT_LIST_HEAD(&card->component_dev_list);
	INIT_LIST_HEAD(&card->list);
	INIT_LIST_HEAD(&card->dai_link_list);
	INIT_LIST_HEAD(&card->rtd_list);
	INIT_LIST_HEAD(&card->dapm_dirty);
	INIT_LIST_HEAD(&card->dobj_list);

	card->num_rtd = 0;
	card->instantiated = 0;
	mutex_init(&card->mutex);
	mutex_init(&card->dapm_mutex);
	mutex_init(&card->pcm_mutex);
	spin_lock_init(&card->dpcm_lock);

	return snd_soc_bind_card(card);
}