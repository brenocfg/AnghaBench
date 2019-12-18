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
struct snd_ctl_elem_id {int /*<<< orphan*/  name; void* iface; } ;
struct snd_card {int /*<<< orphan*/  dev; } ;
struct snd_ac97 {int /*<<< orphan*/  private_data; } ;
typedef  int /*<<< orphan*/  elem ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int EIO ; 
 int /*<<< orphan*/  OLPC_GPIO_MIC_AC ; 
 void* SNDRV_CTL_ELEM_IFACE_MIXER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  machine_is_olpc () ; 
 int /*<<< orphan*/  memset (struct snd_ctl_elem_id*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * olpc_cs5535audio_ctls ; 
 int /*<<< orphan*/  olpc_mic_bias (struct snd_ac97*,int /*<<< orphan*/ ) ; 
 int snd_ctl_add (struct snd_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_remove_id (struct snd_card*,struct snd_ctl_elem_id*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

int olpc_quirks(struct snd_card *card, struct snd_ac97 *ac97)
{
	struct snd_ctl_elem_id elem;
	int i, err;

	if (!machine_is_olpc())
		return 0;

	if (gpio_request(OLPC_GPIO_MIC_AC, DRV_NAME)) {
		dev_err(card->dev, "unable to allocate MIC GPIO\n");
		return -EIO;
	}
	gpio_direction_output(OLPC_GPIO_MIC_AC, 0);

	/* drop the original AD1888 HPF control */
	memset(&elem, 0, sizeof(elem));
	elem.iface = SNDRV_CTL_ELEM_IFACE_MIXER;
	strlcpy(elem.name, "High Pass Filter Enable", sizeof(elem.name));
	snd_ctl_remove_id(card, &elem);

	/* drop the original V_REFOUT control */
	memset(&elem, 0, sizeof(elem));
	elem.iface = SNDRV_CTL_ELEM_IFACE_MIXER;
	strlcpy(elem.name, "V_REFOUT Enable", sizeof(elem.name));
	snd_ctl_remove_id(card, &elem);

	/* add the OLPC-specific controls */
	for (i = 0; i < ARRAY_SIZE(olpc_cs5535audio_ctls); i++) {
		err = snd_ctl_add(card, snd_ctl_new1(&olpc_cs5535audio_ctls[i],
				ac97->private_data));
		if (err < 0) {
			gpio_free(OLPC_GPIO_MIC_AC);
			return err;
		}
	}

	/* turn off the mic by default */
	olpc_mic_bias(ac97, 0);
	return 0;
}