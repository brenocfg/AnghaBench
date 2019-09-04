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
struct snd_pcm_hw_params {int dummy; } ;
struct oxygen {int /*<<< orphan*/  mutex; int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  OXYGEN_PLAY_FORMAT ; 
 int /*<<< orphan*/  OXYGEN_SPDIF_CONTROL ; 
 int /*<<< orphan*/  OXYGEN_SPDIF_FORMAT_MASK ; 
 int OXYGEN_SPDIF_FORMAT_SHIFT ; 
 int /*<<< orphan*/  OXYGEN_SPDIF_OUT_ENABLE ; 
 int /*<<< orphan*/  OXYGEN_SPDIF_OUT_RATE_MASK ; 
 int OXYGEN_SPDIF_OUT_RATE_SHIFT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oxygen_clear_bits32 (struct oxygen*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int oxygen_format (struct snd_pcm_hw_params*) ; 
 int oxygen_hw_params (struct snd_pcm_substream*,struct snd_pcm_hw_params*) ; 
 int oxygen_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  oxygen_update_spdif_source (struct oxygen*) ; 
 int /*<<< orphan*/  oxygen_write32_masked (struct oxygen*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oxygen_write8_masked (struct oxygen*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct oxygen* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int oxygen_spdif_hw_params(struct snd_pcm_substream *substream,
				  struct snd_pcm_hw_params *hw_params)
{
	struct oxygen *chip = snd_pcm_substream_chip(substream);
	int err;

	err = oxygen_hw_params(substream, hw_params);
	if (err < 0)
		return err;

	mutex_lock(&chip->mutex);
	spin_lock_irq(&chip->reg_lock);
	oxygen_clear_bits32(chip, OXYGEN_SPDIF_CONTROL,
			    OXYGEN_SPDIF_OUT_ENABLE);
	oxygen_write8_masked(chip, OXYGEN_PLAY_FORMAT,
			     oxygen_format(hw_params) << OXYGEN_SPDIF_FORMAT_SHIFT,
			     OXYGEN_SPDIF_FORMAT_MASK);
	oxygen_write32_masked(chip, OXYGEN_SPDIF_CONTROL,
			      oxygen_rate(hw_params) << OXYGEN_SPDIF_OUT_RATE_SHIFT,
			      OXYGEN_SPDIF_OUT_RATE_MASK);
	oxygen_update_spdif_source(chip);
	spin_unlock_irq(&chip->reg_lock);
	mutex_unlock(&chip->mutex);
	return 0;
}