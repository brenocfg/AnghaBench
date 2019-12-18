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
struct snd_ymfpci_pcm {scalar_t__ output_rear; } ;
struct snd_ymfpci {scalar_t__ rear_opened; int /*<<< orphan*/  reg_lock; } ;
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct TYPE_2__ {struct snd_ymfpci_pcm* private_data; } ;

/* Variables and functions */
 struct snd_ymfpci* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int snd_ymfpci_playback_close_1 (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ymfpci_close_extension (struct snd_ymfpci*) ; 

__attribute__((used)) static int snd_ymfpci_playback_close(struct snd_pcm_substream *substream)
{
	struct snd_ymfpci *chip = snd_pcm_substream_chip(substream);
	struct snd_ymfpci_pcm *ypcm = substream->runtime->private_data;

	spin_lock_irq(&chip->reg_lock);
	if (ypcm->output_rear && chip->rear_opened > 0) {
		chip->rear_opened--;
		ymfpci_close_extension(chip);
	}
	spin_unlock_irq(&chip->reg_lock);
	return snd_ymfpci_playback_close_1(substream);
}