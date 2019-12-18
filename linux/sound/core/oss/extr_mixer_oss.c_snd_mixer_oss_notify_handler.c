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
struct snd_mixer_oss {int oss_dev_alloc; struct snd_card* card; TYPE_1__* slots; int /*<<< orphan*/  name; int /*<<< orphan*/  reg_mutex; } ;
struct snd_card {int number; struct snd_mixer_oss* mixer_oss; scalar_t__* mixername; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int number; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SNDRV_OSS_DEVICE_TYPE_MIXER ; 
 int /*<<< orphan*/  SNDRV_OSS_INFO_DEV_MIXERS ; 
 int SNDRV_OSS_MAX_MIXERS ; 
 int SND_MIXER_OSS_NOTIFY_DISCONNECT ; 
 int SND_MIXER_OSS_NOTIFY_REGISTER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 struct snd_mixer_oss* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct snd_mixer_oss*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_mixer_oss_build (struct snd_mixer_oss*) ; 
 int /*<<< orphan*/  snd_mixer_oss_f_ops ; 
 int snd_mixer_oss_free1 (struct snd_mixer_oss*) ; 
 int /*<<< orphan*/  snd_mixer_oss_proc_done (struct snd_mixer_oss*) ; 
 int /*<<< orphan*/  snd_mixer_oss_proc_init (struct snd_mixer_oss*) ; 
 int /*<<< orphan*/  snd_oss_info_register (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_oss_info_unregister (int /*<<< orphan*/ ,int) ; 
 int snd_register_oss_device (int /*<<< orphan*/ ,struct snd_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct snd_card*) ; 
 int /*<<< orphan*/  snd_unregister_oss_device (int /*<<< orphan*/ ,struct snd_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static int snd_mixer_oss_notify_handler(struct snd_card *card, int cmd)
{
	struct snd_mixer_oss *mixer;

	if (cmd == SND_MIXER_OSS_NOTIFY_REGISTER) {
		int idx, err;

		mixer = kcalloc(2, sizeof(*mixer), GFP_KERNEL);
		if (mixer == NULL)
			return -ENOMEM;
		mutex_init(&mixer->reg_mutex);
		if ((err = snd_register_oss_device(SNDRV_OSS_DEVICE_TYPE_MIXER,
						   card, 0,
						   &snd_mixer_oss_f_ops, card)) < 0) {
			dev_err(card->dev,
				"unable to register OSS mixer device %i:%i\n",
				card->number, 0);
			kfree(mixer);
			return err;
		}
		mixer->oss_dev_alloc = 1;
		mixer->card = card;
		if (*card->mixername)
			strlcpy(mixer->name, card->mixername, sizeof(mixer->name));
		else
			snprintf(mixer->name, sizeof(mixer->name),
				 "mixer%i", card->number);
#ifdef SNDRV_OSS_INFO_DEV_MIXERS
		snd_oss_info_register(SNDRV_OSS_INFO_DEV_MIXERS,
				      card->number,
				      mixer->name);
#endif
		for (idx = 0; idx < SNDRV_OSS_MAX_MIXERS; idx++)
			mixer->slots[idx].number = idx;
		card->mixer_oss = mixer;
		snd_mixer_oss_build(mixer);
		snd_mixer_oss_proc_init(mixer);
	} else {
		mixer = card->mixer_oss;
		if (mixer == NULL)
			return 0;
		if (mixer->oss_dev_alloc) {
#ifdef SNDRV_OSS_INFO_DEV_MIXERS
			snd_oss_info_unregister(SNDRV_OSS_INFO_DEV_MIXERS, mixer->card->number);
#endif
			snd_unregister_oss_device(SNDRV_OSS_DEVICE_TYPE_MIXER, mixer->card, 0);
			mixer->oss_dev_alloc = 0;
		}
		if (cmd == SND_MIXER_OSS_NOTIFY_DISCONNECT)
			return 0;
		snd_mixer_oss_proc_done(mixer);
		return snd_mixer_oss_free1(mixer);
	}
	return 0;
}