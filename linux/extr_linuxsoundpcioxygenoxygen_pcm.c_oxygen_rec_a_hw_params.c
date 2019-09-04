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
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_2__ {int adc_i2s_format; int /*<<< orphan*/  (* set_adc_params ) (struct oxygen*,struct snd_pcm_hw_params*) ;} ;
struct oxygen {int /*<<< orphan*/  mutex; TYPE_1__ model; int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  OXYGEN_I2S_A_FORMAT ; 
 int OXYGEN_I2S_BITS_MASK ; 
 int OXYGEN_I2S_FORMAT_MASK ; 
 int OXYGEN_I2S_MCLK_MASK ; 
 int OXYGEN_I2S_RATE_MASK ; 
 int /*<<< orphan*/  OXYGEN_REC_FORMAT ; 
 int /*<<< orphan*/  OXYGEN_REC_FORMAT_A_MASK ; 
 int OXYGEN_REC_FORMAT_A_SHIFT ; 
 int /*<<< orphan*/  PCM_A ; 
 int get_mclk (struct oxygen*,int /*<<< orphan*/ ,struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int oxygen_format (struct snd_pcm_hw_params*) ; 
 int oxygen_hw_params (struct snd_pcm_substream*,struct snd_pcm_hw_params*) ; 
 int oxygen_i2s_bits (struct snd_pcm_hw_params*) ; 
 int oxygen_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  oxygen_write16_masked (struct oxygen*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  oxygen_write8_masked (struct oxygen*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct oxygen* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct oxygen*,struct snd_pcm_hw_params*) ; 

__attribute__((used)) static int oxygen_rec_a_hw_params(struct snd_pcm_substream *substream,
				  struct snd_pcm_hw_params *hw_params)
{
	struct oxygen *chip = snd_pcm_substream_chip(substream);
	int err;

	err = oxygen_hw_params(substream, hw_params);
	if (err < 0)
		return err;

	spin_lock_irq(&chip->reg_lock);
	oxygen_write8_masked(chip, OXYGEN_REC_FORMAT,
			     oxygen_format(hw_params) << OXYGEN_REC_FORMAT_A_SHIFT,
			     OXYGEN_REC_FORMAT_A_MASK);
	oxygen_write16_masked(chip, OXYGEN_I2S_A_FORMAT,
			      oxygen_rate(hw_params) |
			      chip->model.adc_i2s_format |
			      get_mclk(chip, PCM_A, hw_params) |
			      oxygen_i2s_bits(hw_params),
			      OXYGEN_I2S_RATE_MASK |
			      OXYGEN_I2S_FORMAT_MASK |
			      OXYGEN_I2S_MCLK_MASK |
			      OXYGEN_I2S_BITS_MASK);
	spin_unlock_irq(&chip->reg_lock);

	mutex_lock(&chip->mutex);
	chip->model.set_adc_params(chip, hw_params);
	mutex_unlock(&chip->mutex);
	return 0;
}