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
struct snd_pcm_substream {TYPE_1__* pcm; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int dummy; } ;
struct snd_bt87x {int /*<<< orphan*/  opened; struct snd_pcm_substream* substream; } ;
struct TYPE_2__ {scalar_t__ device; } ;

/* Variables and functions */
 scalar_t__ DEVICE_DIGITAL ; 
 int EBUSY ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIODS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int snd_bt87x_set_analog_hw (struct snd_bt87x*,struct snd_pcm_runtime*) ; 
 int snd_bt87x_set_digital_hw (struct snd_bt87x*,struct snd_pcm_runtime*) ; 
 int snd_pcm_hw_constraint_integer (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 struct snd_bt87x* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_bt87x_pcm_open(struct snd_pcm_substream *substream)
{
	struct snd_bt87x *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	int err;

	if (test_and_set_bit(0, &chip->opened))
		return -EBUSY;

	if (substream->pcm->device == DEVICE_DIGITAL)
		err = snd_bt87x_set_digital_hw(chip, runtime);
	else
		err = snd_bt87x_set_analog_hw(chip, runtime);
	if (err < 0)
		goto _error;

	err = snd_pcm_hw_constraint_integer(runtime, SNDRV_PCM_HW_PARAM_PERIODS);
	if (err < 0)
		goto _error;

	chip->substream = substream;
	return 0;

_error:
	clear_bit(0, &chip->opened);
	smp_mb__after_atomic();
	return err;
}