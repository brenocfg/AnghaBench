#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_ymfpci {int spdif_bits; TYPE_2__* spdif_pcm_ctl; int /*<<< orphan*/  card; int /*<<< orphan*/  reg_lock; scalar_t__ spdif_opened; } ;
struct snd_pcm_substream {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; TYPE_1__* vd; } ;
struct TYPE_3__ {int /*<<< orphan*/  access; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_ELEM_ACCESS_INACTIVE ; 
 int SNDRV_CTL_EVENT_MASK_INFO ; 
 int SNDRV_CTL_EVENT_MASK_VALUE ; 
 int /*<<< orphan*/  YDSXGR_SPDIFOUTCTRL ; 
 int /*<<< orphan*/  YDSXGR_SPDIFOUTSTATUS ; 
 int /*<<< orphan*/  snd_ctl_notify (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct snd_ymfpci* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int snd_ymfpci_playback_close_1 (struct snd_pcm_substream*) ; 
 int snd_ymfpci_readw (struct snd_ymfpci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ymfpci_writew (struct snd_ymfpci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ymfpci_close_extension (struct snd_ymfpci*) ; 

__attribute__((used)) static int snd_ymfpci_playback_spdif_close(struct snd_pcm_substream *substream)
{
	struct snd_ymfpci *chip = snd_pcm_substream_chip(substream);

	spin_lock_irq(&chip->reg_lock);
	chip->spdif_opened = 0;
	ymfpci_close_extension(chip);
	snd_ymfpci_writew(chip, YDSXGR_SPDIFOUTCTRL,
			  snd_ymfpci_readw(chip, YDSXGR_SPDIFOUTCTRL) & ~2);
	snd_ymfpci_writew(chip, YDSXGR_SPDIFOUTSTATUS, chip->spdif_bits);
	spin_unlock_irq(&chip->reg_lock);
	chip->spdif_pcm_ctl->vd[0].access |= SNDRV_CTL_ELEM_ACCESS_INACTIVE;
	snd_ctl_notify(chip->card, SNDRV_CTL_EVENT_MASK_VALUE |
		       SNDRV_CTL_EVENT_MASK_INFO, &chip->spdif_pcm_ctl->id);
	return snd_ymfpci_playback_close_1(substream);
}