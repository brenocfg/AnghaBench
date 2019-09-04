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
struct xen_snd_front_pcm_instance_info {int dummy; } ;
struct xen_front_cfg_card {int num_pcm_instances; int /*<<< orphan*/  name_long; int /*<<< orphan*/  name_short; int /*<<< orphan*/ * pcm_instances; int /*<<< orphan*/  pcm_hw; } ;
struct xen_snd_front_info {struct xen_snd_front_card_info* card_info; struct xen_front_cfg_card cfg; TYPE_1__* xb_dev; } ;
struct xen_snd_front_card_info {int num_pcm_instances; int /*<<< orphan*/ * pcm_instances; int /*<<< orphan*/  pcm_hw; struct snd_card* card; struct xen_snd_front_info* front_info; } ;
struct snd_card {int /*<<< orphan*/  longname; int /*<<< orphan*/  shortname; int /*<<< orphan*/  driver; struct xen_snd_front_card_info* private_data; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  XENSND_DRIVER_NAME ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/ * devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 int new_pcm_instance (struct xen_snd_front_card_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_card_free (struct snd_card*) ; 
 int snd_card_new (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct snd_card**) ; 
 int snd_card_register (struct snd_card*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int xen_snd_front_alsa_init(struct xen_snd_front_info *front_info)
{
	struct device *dev = &front_info->xb_dev->dev;
	struct xen_front_cfg_card *cfg = &front_info->cfg;
	struct xen_snd_front_card_info *card_info;
	struct snd_card *card;
	int ret, i;

	dev_dbg(dev, "Creating virtual sound card\n");

	ret = snd_card_new(dev, 0, XENSND_DRIVER_NAME, THIS_MODULE,
			   sizeof(struct xen_snd_front_card_info), &card);
	if (ret < 0)
		return ret;

	card_info = card->private_data;
	card_info->front_info = front_info;
	front_info->card_info = card_info;
	card_info->card = card;
	card_info->pcm_instances =
			devm_kcalloc(dev, cfg->num_pcm_instances,
				     sizeof(struct xen_snd_front_pcm_instance_info),
				     GFP_KERNEL);
	if (!card_info->pcm_instances) {
		ret = -ENOMEM;
		goto fail;
	}

	card_info->num_pcm_instances = cfg->num_pcm_instances;
	card_info->pcm_hw = cfg->pcm_hw;

	for (i = 0; i < cfg->num_pcm_instances; i++) {
		ret = new_pcm_instance(card_info, &cfg->pcm_instances[i],
				       &card_info->pcm_instances[i]);
		if (ret < 0)
			goto fail;
	}

	strncpy(card->driver, XENSND_DRIVER_NAME, sizeof(card->driver));
	strncpy(card->shortname, cfg->name_short, sizeof(card->shortname));
	strncpy(card->longname, cfg->name_long, sizeof(card->longname));

	ret = snd_card_register(card);
	if (ret < 0)
		goto fail;

	return 0;

fail:
	snd_card_free(card);
	return ret;
}