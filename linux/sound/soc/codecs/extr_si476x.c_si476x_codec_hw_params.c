#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai {TYPE_1__* component; int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct si476x_core {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SI476X_DIGITAL_IO_OUTPUT_FORMAT ; 
 int /*<<< orphan*/  SI476X_DIGITAL_IO_OUTPUT_SAMPLE_RATE ; 
 int /*<<< orphan*/  SI476X_DIGITAL_IO_OUTPUT_WIDTH_MASK ; 
 int SI476X_DIGITAL_IO_SAMPLE_SIZE_SHIFT ; 
 int SI476X_DIGITAL_IO_SLOT_SIZE_SHIFT ; 
 int SI476X_PCM_FORMAT_S16_LE ; 
 int SI476X_PCM_FORMAT_S20_3LE ; 
 int SI476X_PCM_FORMAT_S24_LE ; 
 int SI476X_PCM_FORMAT_S8 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct si476x_core* i2c_mfd_cell_to_core (int /*<<< orphan*/ ) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  si476x_core_lock (struct si476x_core*) ; 
 int /*<<< orphan*/  si476x_core_unlock (struct si476x_core*) ; 
 int snd_soc_component_update_bits (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int snd_soc_component_write (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int si476x_codec_hw_params(struct snd_pcm_substream *substream,
				  struct snd_pcm_hw_params *params,
				  struct snd_soc_dai *dai)
{
	struct si476x_core *core = i2c_mfd_cell_to_core(dai->dev);
	int rate, width, err;

	rate = params_rate(params);
	if (rate < 32000 || rate > 48000) {
		dev_err(dai->component->dev, "Rate: %d is not supported\n", rate);
		return -EINVAL;
	}

	switch (params_width(params)) {
	case 8:
		width = SI476X_PCM_FORMAT_S8;
		break;
	case 16:
		width = SI476X_PCM_FORMAT_S16_LE;
		break;
	case 20:
		width = SI476X_PCM_FORMAT_S20_3LE;
		break;
	case 24:
		width = SI476X_PCM_FORMAT_S24_LE;
		break;
	default:
		return -EINVAL;
	}

	si476x_core_lock(core);

	err = snd_soc_component_write(dai->component, SI476X_DIGITAL_IO_OUTPUT_SAMPLE_RATE,
			    rate);
	if (err < 0) {
		dev_err(dai->component->dev, "Failed to set sample rate\n");
		goto out;
	}

	err = snd_soc_component_update_bits(dai->component, SI476X_DIGITAL_IO_OUTPUT_FORMAT,
				  SI476X_DIGITAL_IO_OUTPUT_WIDTH_MASK,
				  (width << SI476X_DIGITAL_IO_SLOT_SIZE_SHIFT) |
				  (width << SI476X_DIGITAL_IO_SAMPLE_SIZE_SHIFT));
	if (err < 0) {
		dev_err(dai->component->dev, "Failed to set output width\n");
		goto out;
	}

out:
	si476x_core_unlock(core);

	return err;
}