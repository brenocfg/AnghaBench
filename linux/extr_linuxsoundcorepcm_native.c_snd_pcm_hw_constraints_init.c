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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_hw_constraints {int dummy; } ;
struct snd_pcm_runtime {struct snd_pcm_hw_constraints hw_constraints; } ;

/* Variables and functions */
 int SNDRV_PCM_HW_PARAM_BUFFER_BYTES ; 
 int SNDRV_PCM_HW_PARAM_BUFFER_SIZE ; 
 int SNDRV_PCM_HW_PARAM_BUFFER_TIME ; 
 int SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int SNDRV_PCM_HW_PARAM_FIRST_INTERVAL ; 
 int SNDRV_PCM_HW_PARAM_FIRST_MASK ; 
 int SNDRV_PCM_HW_PARAM_FORMAT ; 
 int SNDRV_PCM_HW_PARAM_FRAME_BITS ; 
 int SNDRV_PCM_HW_PARAM_LAST_INTERVAL ; 
 int SNDRV_PCM_HW_PARAM_LAST_MASK ; 
 int SNDRV_PCM_HW_PARAM_PERIODS ; 
 int SNDRV_PCM_HW_PARAM_PERIOD_BYTES ; 
 int SNDRV_PCM_HW_PARAM_PERIOD_SIZE ; 
 int SNDRV_PCM_HW_PARAM_PERIOD_TIME ; 
 int SNDRV_PCM_HW_PARAM_RATE ; 
 int SNDRV_PCM_HW_PARAM_SAMPLE_BITS ; 
 int /*<<< orphan*/  constrs_interval (struct snd_pcm_hw_constraints*,int) ; 
 int /*<<< orphan*/  constrs_mask (struct snd_pcm_hw_constraints*,int) ; 
 int /*<<< orphan*/  snd_interval_any (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_interval_setinteger (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mask_any (int /*<<< orphan*/ ) ; 
 int snd_pcm_hw_rule_add (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*,int,int,...) ; 
 int /*<<< orphan*/  snd_pcm_hw_rule_div ; 
 int /*<<< orphan*/  snd_pcm_hw_rule_format ; 
 int /*<<< orphan*/  snd_pcm_hw_rule_mul ; 
 int /*<<< orphan*/  snd_pcm_hw_rule_muldivk ; 
 int /*<<< orphan*/  snd_pcm_hw_rule_mulkdiv ; 
 int /*<<< orphan*/  snd_pcm_hw_rule_sample_bits ; 

int snd_pcm_hw_constraints_init(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_pcm_hw_constraints *constrs = &runtime->hw_constraints;
	int k, err;

	for (k = SNDRV_PCM_HW_PARAM_FIRST_MASK; k <= SNDRV_PCM_HW_PARAM_LAST_MASK; k++) {
		snd_mask_any(constrs_mask(constrs, k));
	}

	for (k = SNDRV_PCM_HW_PARAM_FIRST_INTERVAL; k <= SNDRV_PCM_HW_PARAM_LAST_INTERVAL; k++) {
		snd_interval_any(constrs_interval(constrs, k));
	}

	snd_interval_setinteger(constrs_interval(constrs, SNDRV_PCM_HW_PARAM_CHANNELS));
	snd_interval_setinteger(constrs_interval(constrs, SNDRV_PCM_HW_PARAM_BUFFER_SIZE));
	snd_interval_setinteger(constrs_interval(constrs, SNDRV_PCM_HW_PARAM_BUFFER_BYTES));
	snd_interval_setinteger(constrs_interval(constrs, SNDRV_PCM_HW_PARAM_SAMPLE_BITS));
	snd_interval_setinteger(constrs_interval(constrs, SNDRV_PCM_HW_PARAM_FRAME_BITS));

	err = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_FORMAT,
				   snd_pcm_hw_rule_format, NULL,
				   SNDRV_PCM_HW_PARAM_SAMPLE_BITS, -1);
	if (err < 0)
		return err;
	err = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_SAMPLE_BITS, 
				  snd_pcm_hw_rule_sample_bits, NULL,
				  SNDRV_PCM_HW_PARAM_FORMAT, 
				  SNDRV_PCM_HW_PARAM_SAMPLE_BITS, -1);
	if (err < 0)
		return err;
	err = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_SAMPLE_BITS, 
				  snd_pcm_hw_rule_div, NULL,
				  SNDRV_PCM_HW_PARAM_FRAME_BITS, SNDRV_PCM_HW_PARAM_CHANNELS, -1);
	if (err < 0)
		return err;
	err = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_FRAME_BITS, 
				  snd_pcm_hw_rule_mul, NULL,
				  SNDRV_PCM_HW_PARAM_SAMPLE_BITS, SNDRV_PCM_HW_PARAM_CHANNELS, -1);
	if (err < 0)
		return err;
	err = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_FRAME_BITS, 
				  snd_pcm_hw_rule_mulkdiv, (void*) 8,
				  SNDRV_PCM_HW_PARAM_PERIOD_BYTES, SNDRV_PCM_HW_PARAM_PERIOD_SIZE, -1);
	if (err < 0)
		return err;
	err = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_FRAME_BITS, 
				  snd_pcm_hw_rule_mulkdiv, (void*) 8,
				  SNDRV_PCM_HW_PARAM_BUFFER_BYTES, SNDRV_PCM_HW_PARAM_BUFFER_SIZE, -1);
	if (err < 0)
		return err;
	err = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_CHANNELS, 
				  snd_pcm_hw_rule_div, NULL,
				  SNDRV_PCM_HW_PARAM_FRAME_BITS, SNDRV_PCM_HW_PARAM_SAMPLE_BITS, -1);
	if (err < 0)
		return err;
	err = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_RATE, 
				  snd_pcm_hw_rule_mulkdiv, (void*) 1000000,
				  SNDRV_PCM_HW_PARAM_PERIOD_SIZE, SNDRV_PCM_HW_PARAM_PERIOD_TIME, -1);
	if (err < 0)
		return err;
	err = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_RATE, 
				  snd_pcm_hw_rule_mulkdiv, (void*) 1000000,
				  SNDRV_PCM_HW_PARAM_BUFFER_SIZE, SNDRV_PCM_HW_PARAM_BUFFER_TIME, -1);
	if (err < 0)
		return err;
	err = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_PERIODS, 
				  snd_pcm_hw_rule_div, NULL,
				  SNDRV_PCM_HW_PARAM_BUFFER_SIZE, SNDRV_PCM_HW_PARAM_PERIOD_SIZE, -1);
	if (err < 0)
		return err;
	err = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_PERIOD_SIZE, 
				  snd_pcm_hw_rule_div, NULL,
				  SNDRV_PCM_HW_PARAM_BUFFER_SIZE, SNDRV_PCM_HW_PARAM_PERIODS, -1);
	if (err < 0)
		return err;
	err = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_PERIOD_SIZE, 
				  snd_pcm_hw_rule_mulkdiv, (void*) 8,
				  SNDRV_PCM_HW_PARAM_PERIOD_BYTES, SNDRV_PCM_HW_PARAM_FRAME_BITS, -1);
	if (err < 0)
		return err;
	err = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_PERIOD_SIZE, 
				  snd_pcm_hw_rule_muldivk, (void*) 1000000,
				  SNDRV_PCM_HW_PARAM_PERIOD_TIME, SNDRV_PCM_HW_PARAM_RATE, -1);
	if (err < 0)
		return err;
	err = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_BUFFER_SIZE, 
				  snd_pcm_hw_rule_mul, NULL,
				  SNDRV_PCM_HW_PARAM_PERIOD_SIZE, SNDRV_PCM_HW_PARAM_PERIODS, -1);
	if (err < 0)
		return err;
	err = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_BUFFER_SIZE, 
				  snd_pcm_hw_rule_mulkdiv, (void*) 8,
				  SNDRV_PCM_HW_PARAM_BUFFER_BYTES, SNDRV_PCM_HW_PARAM_FRAME_BITS, -1);
	if (err < 0)
		return err;
	err = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_BUFFER_SIZE, 
				  snd_pcm_hw_rule_muldivk, (void*) 1000000,
				  SNDRV_PCM_HW_PARAM_BUFFER_TIME, SNDRV_PCM_HW_PARAM_RATE, -1);
	if (err < 0)
		return err;
	err = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_PERIOD_BYTES, 
				  snd_pcm_hw_rule_muldivk, (void*) 8,
				  SNDRV_PCM_HW_PARAM_PERIOD_SIZE, SNDRV_PCM_HW_PARAM_FRAME_BITS, -1);
	if (err < 0)
		return err;
	err = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_BUFFER_BYTES, 
				  snd_pcm_hw_rule_muldivk, (void*) 8,
				  SNDRV_PCM_HW_PARAM_BUFFER_SIZE, SNDRV_PCM_HW_PARAM_FRAME_BITS, -1);
	if (err < 0)
		return err;
	err = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_PERIOD_TIME, 
				  snd_pcm_hw_rule_mulkdiv, (void*) 1000000,
				  SNDRV_PCM_HW_PARAM_PERIOD_SIZE, SNDRV_PCM_HW_PARAM_RATE, -1);
	if (err < 0)
		return err;
	err = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_BUFFER_TIME, 
				  snd_pcm_hw_rule_mulkdiv, (void*) 1000000,
				  SNDRV_PCM_HW_PARAM_BUFFER_SIZE, SNDRV_PCM_HW_PARAM_RATE, -1);
	if (err < 0)
		return err;
	return 0;
}