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
struct snd_kcontrol_new {int /*<<< orphan*/  name; } ;
struct snd_kcontrol {int dummy; } ;
struct snd_card {int /*<<< orphan*/  mixername; } ;
struct snd_ca0106 {TYPE_1__* details; struct snd_card* card; } ;
struct TYPE_2__ {int i2c_adc; int gpio_type; scalar_t__ spi_dac; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_CTLS (struct snd_ca0106*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  add_slaves (struct snd_card*,struct snd_kcontrol*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_ctl (struct snd_card*,char*) ; 
 int /*<<< orphan*/  rename_ctl (struct snd_card*,char*,char*) ; 
 int /*<<< orphan*/  slave_sws ; 
 int /*<<< orphan*/  slave_vols ; 
 struct snd_kcontrol_new snd_ca0106_capture_line_in_side_out ; 
 struct snd_kcontrol_new snd_ca0106_capture_mic_line_in ; 
 int /*<<< orphan*/ * snd_ca0106_master_db_scale ; 
 int /*<<< orphan*/  snd_ca0106_volume_ctls ; 
 int /*<<< orphan*/  snd_ca0106_volume_i2c_adc_ctls ; 
 struct snd_kcontrol_new snd_ca0106_volume_spi_dac_ctl (TYPE_1__*,int) ; 
 int snd_ctl_add (struct snd_card*,struct snd_kcontrol*) ; 
 struct snd_kcontrol* snd_ctl_make_virtual_master (char*,int /*<<< orphan*/ *) ; 
 struct snd_kcontrol* snd_ctl_new1 (struct snd_kcontrol_new*,struct snd_ca0106*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

int snd_ca0106_mixer(struct snd_ca0106 *emu)
{
	int err;
        struct snd_card *card = emu->card;
	char **c;
	struct snd_kcontrol *vmaster;
	static char *ca0106_remove_ctls[] = {
		"Master Mono Playback Switch",
		"Master Mono Playback Volume",
		"3D Control - Switch",
		"3D Control Sigmatel - Depth",
		"PCM Playback Switch",
		"PCM Playback Volume",
		"CD Playback Switch",
		"CD Playback Volume",
		"Phone Playback Switch",
		"Phone Playback Volume",
		"Video Playback Switch",
		"Video Playback Volume",
		"Beep Playback Switch",
		"Beep Playback Volume",
		"Mono Output Select",
		"Capture Source",
		"Capture Switch",
		"Capture Volume",
		"External Amplifier",
		"Sigmatel 4-Speaker Stereo Playback Switch",
		"Surround Phase Inversion Playback Switch",
		NULL
	};
	static char *ca0106_rename_ctls[] = {
		"Master Playback Switch", "Capture Switch",
		"Master Playback Volume", "Capture Volume",
		"Line Playback Switch", "AC97 Line Capture Switch",
		"Line Playback Volume", "AC97 Line Capture Volume",
		"Aux Playback Switch", "AC97 Aux Capture Switch",
		"Aux Playback Volume", "AC97 Aux Capture Volume",
		"Mic Playback Switch", "AC97 Mic Capture Switch",
		"Mic Playback Volume", "AC97 Mic Capture Volume",
		"Mic Select", "AC97 Mic Select",
		"Mic Boost (+20dB)", "AC97 Mic Boost (+20dB)",
		NULL
	};
#if 1
	for (c = ca0106_remove_ctls; *c; c++)
		remove_ctl(card, *c);
	for (c = ca0106_rename_ctls; *c; c += 2)
		rename_ctl(card, c[0], c[1]);
#endif

	ADD_CTLS(emu, snd_ca0106_volume_ctls);
	if (emu->details->i2c_adc == 1) {
		ADD_CTLS(emu, snd_ca0106_volume_i2c_adc_ctls);
		if (emu->details->gpio_type == 1)
			err = snd_ctl_add(card, snd_ctl_new1(&snd_ca0106_capture_mic_line_in, emu));
		else  /* gpio_type == 2 */
			err = snd_ctl_add(card, snd_ctl_new1(&snd_ca0106_capture_line_in_side_out, emu));
		if (err < 0)
			return err;
	}
	if (emu->details->spi_dac) {
		int i;
		for (i = 0;; i++) {
			struct snd_kcontrol_new ctl;
			ctl = snd_ca0106_volume_spi_dac_ctl(emu->details, i);
			if (!ctl.name)
				break;
			err = snd_ctl_add(card, snd_ctl_new1(&ctl, emu));
			if (err < 0)
				return err;
		}
	}

	/* Create virtual master controls */
	vmaster = snd_ctl_make_virtual_master("Master Playback Volume",
					      snd_ca0106_master_db_scale);
	if (!vmaster)
		return -ENOMEM;
	err = snd_ctl_add(card, vmaster);
	if (err < 0)
		return err;
	add_slaves(card, vmaster, slave_vols);

	if (emu->details->spi_dac) {
		vmaster = snd_ctl_make_virtual_master("Master Playback Switch",
						      NULL);
		if (!vmaster)
			return -ENOMEM;
		err = snd_ctl_add(card, vmaster);
		if (err < 0)
			return err;
		add_slaves(card, vmaster, slave_sws);
	}

	strcpy(card->mixername, "CA0106");
        return 0;
}