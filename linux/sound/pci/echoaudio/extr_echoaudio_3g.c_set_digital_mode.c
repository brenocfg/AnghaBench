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
typedef  int u8 ;
struct echoaudio {int pipe_alloc_mask; int digital_modes; int digital_mode; int /*<<< orphan*/  lock; int /*<<< orphan*/ * output_gain; int /*<<< orphan*/ * input_gain; int /*<<< orphan*/ ** monitor_gain; } ;

/* Variables and functions */
 int DIGITAL_MODE_ADAT ; 
 int EAGAIN ; 
 int EINVAL ; 
 int dsp_set_digital_mode (struct echoaudio*,int) ; 
 int num_busses_in (struct echoaudio*) ; 
 int num_busses_out (struct echoaudio*) ; 
 int /*<<< orphan*/  set_input_gain (struct echoaudio*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_monitor_gain (struct echoaudio*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_output_gain (struct echoaudio*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_input_line_level (struct echoaudio*) ; 
 int /*<<< orphan*/  update_output_line_level (struct echoaudio*) ; 

__attribute__((used)) static int set_digital_mode(struct echoaudio *chip, u8 mode)
{
	u8 previous_mode;
	int err, i, o;

	/* All audio channels must be closed before changing the digital mode */
	if (snd_BUG_ON(chip->pipe_alloc_mask))
		return -EAGAIN;

	if (snd_BUG_ON(!(chip->digital_modes & (1 << mode))))
		return -EINVAL;

	previous_mode = chip->digital_mode;
	err = dsp_set_digital_mode(chip, mode);

	/* If we successfully changed the digital mode from or to ADAT,
	 * then make sure all output, input and monitor levels are
	 * updated by the DSP comm object. */
	if (err >= 0 && previous_mode != mode &&
	    (previous_mode == DIGITAL_MODE_ADAT || mode == DIGITAL_MODE_ADAT)) {
		spin_lock_irq(&chip->lock);
		for (o = 0; o < num_busses_out(chip); o++)
			for (i = 0; i < num_busses_in(chip); i++)
				set_monitor_gain(chip, o, i,
						 chip->monitor_gain[o][i]);

#ifdef ECHOCARD_HAS_INPUT_GAIN
		for (i = 0; i < num_busses_in(chip); i++)
			set_input_gain(chip, i, chip->input_gain[i]);
		update_input_line_level(chip);
#endif

		for (o = 0; o < num_busses_out(chip); o++)
			set_output_gain(chip, o, chip->output_gain[o]);
		update_output_line_level(chip);
		spin_unlock_irq(&chip->lock);
	}

	return err;
}