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
struct oxygen {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  OXYGEN_SPDIF_CONTROL ; 
 int /*<<< orphan*/  OXYGEN_SPDIF_OUT_ENABLE ; 
 int /*<<< orphan*/  oxygen_clear_bits32 (struct oxygen*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int oxygen_hw_free (struct snd_pcm_substream*) ; 
 struct oxygen* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int oxygen_spdif_hw_free(struct snd_pcm_substream *substream)
{
	struct oxygen *chip = snd_pcm_substream_chip(substream);

	spin_lock_irq(&chip->reg_lock);
	oxygen_clear_bits32(chip, OXYGEN_SPDIF_CONTROL,
			    OXYGEN_SPDIF_OUT_ENABLE);
	spin_unlock_irq(&chip->reg_lock);
	return oxygen_hw_free(substream);
}