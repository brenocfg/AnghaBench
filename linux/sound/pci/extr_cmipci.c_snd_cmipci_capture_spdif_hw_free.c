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
struct snd_pcm_substream {int dummy; } ;
struct cmipci {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_CAPTURE_SPDF ; 
 int /*<<< orphan*/  CM_REG_FUNCTRL1 ; 
 int /*<<< orphan*/  CM_REG_MISC_CTRL ; 
 int /*<<< orphan*/  CM_SPD32SEL ; 
 int /*<<< orphan*/  snd_cmipci_clear_bit (struct cmipci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_cmipci_hw_free (struct snd_pcm_substream*) ; 
 struct cmipci* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_cmipci_capture_spdif_hw_free(struct snd_pcm_substream *subs)
{
	struct cmipci *cm = snd_pcm_substream_chip(subs);

	spin_lock_irq(&cm->reg_lock);
	snd_cmipci_clear_bit(cm, CM_REG_FUNCTRL1, CM_CAPTURE_SPDF);
	snd_cmipci_clear_bit(cm, CM_REG_MISC_CTRL, CM_SPD32SEL);
	spin_unlock_irq(&cm->reg_lock);

	return snd_cmipci_hw_free(subs);
}