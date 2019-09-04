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
struct snd_kcontrol_new {int /*<<< orphan*/  put; int /*<<< orphan*/  get; int /*<<< orphan*/  info; int /*<<< orphan*/  access; } ;
struct snd_card_asihpi {struct snd_card* card; } ;
struct snd_card {int dummy; } ;
struct hpi_control {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_ELEM_ACCESS_READWRITE ; 
 int /*<<< orphan*/  asihpi_ctl_init (struct snd_kcontrol_new*,struct hpi_control*,char*) ; 
 int ctl_add (struct snd_card*,struct snd_kcontrol_new*,struct snd_card_asihpi*) ; 
 int /*<<< orphan*/  snd_asihpi_aesebu_format_info ; 
 int /*<<< orphan*/  snd_asihpi_aesebu_tx_format_get ; 
 int /*<<< orphan*/  snd_asihpi_aesebu_tx_format_put ; 

__attribute__((used)) static int snd_asihpi_aesebu_tx_add(struct snd_card_asihpi *asihpi,
				    struct hpi_control *hpi_ctl)
{
	struct snd_card *card = asihpi->card;
	struct snd_kcontrol_new snd_control;

	asihpi_ctl_init(&snd_control, hpi_ctl, "Format");
	snd_control.access = SNDRV_CTL_ELEM_ACCESS_READWRITE;
	snd_control.info = snd_asihpi_aesebu_format_info;
	snd_control.get = snd_asihpi_aesebu_tx_format_get;
	snd_control.put = snd_asihpi_aesebu_tx_format_put;

	return ctl_add(card, &snd_control, asihpi);
}