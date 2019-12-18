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
struct TYPE_2__ {int /*<<< orphan*/  p; } ;
struct snd_kcontrol_new {int access; TYPE_1__ tlv; int /*<<< orphan*/  put; int /*<<< orphan*/  get; int /*<<< orphan*/  info; } ;
struct snd_card_asihpi {struct snd_card* card; } ;
struct snd_card {int dummy; } ;
struct hpi_control {int dummy; } ;

/* Variables and functions */
 int SNDRV_CTL_ELEM_ACCESS_READWRITE ; 
 int SNDRV_CTL_ELEM_ACCESS_TLV_READ ; 
 int /*<<< orphan*/  asihpi_ctl_init (struct snd_kcontrol_new*,struct hpi_control*,char*) ; 
 int ctl_add (struct snd_card*,struct snd_kcontrol_new*,struct snd_card_asihpi*) ; 
 int /*<<< orphan*/  db_scale_level ; 
 int /*<<< orphan*/  snd_asihpi_level_get ; 
 int /*<<< orphan*/  snd_asihpi_level_info ; 
 int /*<<< orphan*/  snd_asihpi_level_put ; 

__attribute__((used)) static int snd_asihpi_level_add(struct snd_card_asihpi *asihpi,
				struct hpi_control *hpi_ctl)
{
	struct snd_card *card = asihpi->card;
	struct snd_kcontrol_new snd_control;

	/* can't use 'volume' cos some nodes have volume as well */
	asihpi_ctl_init(&snd_control, hpi_ctl, "Level");
	snd_control.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |
				SNDRV_CTL_ELEM_ACCESS_TLV_READ;
	snd_control.info = snd_asihpi_level_info;
	snd_control.get = snd_asihpi_level_get;
	snd_control.put = snd_asihpi_level_put;
	snd_control.tlv.p = db_scale_level;

	return ctl_add(card, &snd_control, asihpi);
}