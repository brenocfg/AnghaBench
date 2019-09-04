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
struct snd_kcontrol_new {int access; int /*<<< orphan*/  get; int /*<<< orphan*/  info; int /*<<< orphan*/  put; } ;
struct snd_card_asihpi {struct snd_card* card; } ;
struct snd_card {int dummy; } ;
struct hpi_control {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int SNDRV_CTL_ELEM_ACCESS_READ ; 
 int SNDRV_CTL_ELEM_ACCESS_READWRITE ; 
 int SNDRV_CTL_ELEM_ACCESS_VOLATILE ; 
 int /*<<< orphan*/  asihpi_ctl_init (struct snd_kcontrol_new*,struct hpi_control*,char*) ; 
 int ctl_add (struct snd_card*,struct snd_kcontrol_new*,struct snd_card_asihpi*) ; 
 int /*<<< orphan*/  snd_asihpi_aesebu_format_info ; 
 int /*<<< orphan*/  snd_asihpi_aesebu_rx_format_get ; 
 int /*<<< orphan*/  snd_asihpi_aesebu_rx_format_put ; 
 int /*<<< orphan*/  snd_asihpi_aesebu_rxstatus_get ; 
 int /*<<< orphan*/  snd_asihpi_aesebu_rxstatus_info ; 

__attribute__((used)) static int snd_asihpi_aesebu_rx_add(struct snd_card_asihpi *asihpi,
				    struct hpi_control *hpi_ctl)
{
	struct snd_card *card = asihpi->card;
	struct snd_kcontrol_new snd_control;

	asihpi_ctl_init(&snd_control, hpi_ctl, "Format");
	snd_control.access = SNDRV_CTL_ELEM_ACCESS_READWRITE;
	snd_control.info = snd_asihpi_aesebu_format_info;
	snd_control.get = snd_asihpi_aesebu_rx_format_get;
	snd_control.put = snd_asihpi_aesebu_rx_format_put;


	if (ctl_add(card, &snd_control, asihpi) < 0)
		return -EINVAL;

	asihpi_ctl_init(&snd_control, hpi_ctl, "Status");
	snd_control.access =
	    SNDRV_CTL_ELEM_ACCESS_VOLATILE | SNDRV_CTL_ELEM_ACCESS_READ;
	snd_control.info = snd_asihpi_aesebu_rxstatus_info;
	snd_control.get = snd_asihpi_aesebu_rxstatus_get;

	return ctl_add(card, &snd_control, asihpi);
}