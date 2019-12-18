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
struct snd_kcontrol_new {int /*<<< orphan*/  put; int /*<<< orphan*/  get; int /*<<< orphan*/  info; int /*<<< orphan*/  access; int /*<<< orphan*/  private_value; } ;
struct snd_card_asihpi {struct snd_card* card; } ;
struct snd_card {int dummy; } ;
struct hpi_control {int /*<<< orphan*/  h_control; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_ACCESS_READWRITE ; 
 int /*<<< orphan*/  asihpi_ctl_init (struct snd_kcontrol_new*,struct hpi_control*,char*) ; 
 int ctl_add (struct snd_card*,struct snd_kcontrol_new*,struct snd_card_asihpi*) ; 
 int /*<<< orphan*/  hpi_tuner_get_gain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_asihpi_tuner_band_get ; 
 int /*<<< orphan*/  snd_asihpi_tuner_band_info ; 
 int /*<<< orphan*/  snd_asihpi_tuner_band_put ; 
 int /*<<< orphan*/  snd_asihpi_tuner_freq_get ; 
 int /*<<< orphan*/  snd_asihpi_tuner_freq_info ; 
 int /*<<< orphan*/  snd_asihpi_tuner_freq_put ; 
 int /*<<< orphan*/  snd_asihpi_tuner_gain_get ; 
 int /*<<< orphan*/  snd_asihpi_tuner_gain_info ; 
 int /*<<< orphan*/  snd_asihpi_tuner_gain_put ; 

__attribute__((used)) static int snd_asihpi_tuner_add(struct snd_card_asihpi *asihpi,
				struct hpi_control *hpi_ctl)
{
	struct snd_card *card = asihpi->card;
	struct snd_kcontrol_new snd_control;

	snd_control.private_value = hpi_ctl->h_control;
	snd_control.access = SNDRV_CTL_ELEM_ACCESS_READWRITE;

	if (!hpi_tuner_get_gain(hpi_ctl->h_control, NULL)) {
		asihpi_ctl_init(&snd_control, hpi_ctl, "Gain");
		snd_control.info = snd_asihpi_tuner_gain_info;
		snd_control.get = snd_asihpi_tuner_gain_get;
		snd_control.put = snd_asihpi_tuner_gain_put;

		if (ctl_add(card, &snd_control, asihpi) < 0)
			return -EINVAL;
	}

	asihpi_ctl_init(&snd_control, hpi_ctl, "Band");
	snd_control.info = snd_asihpi_tuner_band_info;
	snd_control.get = snd_asihpi_tuner_band_get;
	snd_control.put = snd_asihpi_tuner_band_put;

	if (ctl_add(card, &snd_control, asihpi) < 0)
		return -EINVAL;

	asihpi_ctl_init(&snd_control, hpi_ctl, "Freq");
	snd_control.info = snd_asihpi_tuner_freq_info;
	snd_control.get = snd_asihpi_tuner_freq_get;
	snd_control.put = snd_asihpi_tuner_freq_put;

	return ctl_add(card, &snd_control, asihpi);
}