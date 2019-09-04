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
typedef  int /*<<< orphan*/  u16 ;
struct snd_pcm {struct channel* private_data; } ;
struct snd_card {char* shortname; int number; int /*<<< orphan*/  longname; int /*<<< orphan*/  driver; struct channel* private_data; } ;
struct most_interface {char* description; int /*<<< orphan*/  dev; } ;
struct most_channel_config {scalar_t__ data_type; scalar_t__ direction; } ;
struct channel {int id; int /*<<< orphan*/  list; int /*<<< orphan*/  pcm_hardware; int /*<<< orphan*/  playback_waitq; struct most_interface* iface; struct most_channel_config* cfg; struct snd_card* card; } ;

/* Variables and functions */
 char* DRIVER_NAME ; 
 int EINVAL ; 
 scalar_t__ MOST_CH_SYNC ; 
 scalar_t__ MOST_CH_TX ; 
 int SNDRV_PCM_STREAM_CAPTURE ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int audio_set_hw_params (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,struct most_channel_config*) ; 
 int /*<<< orphan*/  dev_list ; 
 scalar_t__ get_channel (struct most_interface*,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcm_ops ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  snd_card_free (struct snd_card*) ; 
 int snd_card_new (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ,int,struct snd_card**) ; 
 int snd_card_register (struct snd_card*) ; 
 int snd_pcm_new (struct snd_card*,char*,int /*<<< orphan*/ ,int,int,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int split_arg_list (char*,char**,int /*<<< orphan*/ *,char**) ; 

__attribute__((used)) static int audio_probe_channel(struct most_interface *iface, int channel_id,
			       struct most_channel_config *cfg,
			       char *arg_list)
{
	struct channel *channel;
	struct snd_card *card;
	struct snd_pcm *pcm;
	int playback_count = 0;
	int capture_count = 0;
	int ret;
	int direction;
	char *card_name;
	u16 ch_num;
	char *sample_res;

	if (!iface)
		return -EINVAL;

	if (cfg->data_type != MOST_CH_SYNC) {
		pr_err("Incompatible channel type\n");
		return -EINVAL;
	}

	if (get_channel(iface, channel_id)) {
		pr_err("channel (%s:%d) is already linked\n",
		       iface->description, channel_id);
		return -EINVAL;
	}

	if (cfg->direction == MOST_CH_TX) {
		playback_count = 1;
		direction = SNDRV_PCM_STREAM_PLAYBACK;
	} else {
		capture_count = 1;
		direction = SNDRV_PCM_STREAM_CAPTURE;
	}

	ret = split_arg_list(arg_list, &card_name, &ch_num, &sample_res);
	if (ret < 0)
		return ret;

	ret = snd_card_new(&iface->dev, -1, card_name, THIS_MODULE,
			   sizeof(*channel), &card);
	if (ret < 0)
		return ret;

	channel = card->private_data;
	channel->card = card;
	channel->cfg = cfg;
	channel->iface = iface;
	channel->id = channel_id;
	init_waitqueue_head(&channel->playback_waitq);

	ret = audio_set_hw_params(&channel->pcm_hardware, ch_num, sample_res,
				  cfg);
	if (ret)
		goto err_free_card;

	snprintf(card->driver, sizeof(card->driver), "%s", DRIVER_NAME);
	snprintf(card->shortname, sizeof(card->shortname), "Microchip MOST:%d",
		 card->number);
	snprintf(card->longname, sizeof(card->longname), "%s at %s, ch %d",
		 card->shortname, iface->description, channel_id);

	ret = snd_pcm_new(card, card_name, 0, playback_count,
			  capture_count, &pcm);
	if (ret < 0)
		goto err_free_card;

	pcm->private_data = channel;

	snd_pcm_set_ops(pcm, direction, &pcm_ops);

	ret = snd_card_register(card);
	if (ret < 0)
		goto err_free_card;

	list_add_tail(&channel->list, &dev_list);

	return 0;

err_free_card:
	snd_card_free(card);
	return ret;
}