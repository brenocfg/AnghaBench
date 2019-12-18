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
struct echoaudio {int /*<<< orphan*/  output_clock; int /*<<< orphan*/  input_clock; int /*<<< orphan*/  phantom_power; int /*<<< orphan*/  professional_spdif; int /*<<< orphan*/  digital_mode; scalar_t__ meters_enabled; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/ * input_gain; int /*<<< orphan*/ ** monitor_gain; int /*<<< orphan*/ ** vmixer_gain; int /*<<< orphan*/ * output_gain; TYPE_1__* comm_page; } ;
struct TYPE_2__ {int /*<<< orphan*/  handshake; int /*<<< orphan*/  gd_spdif_status; int /*<<< orphan*/  gd_clock_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSP_VC_METERS_ON ; 
 int /*<<< orphan*/  DSP_VC_UPDATE_FLAGS ; 
 int EIO ; 
 int /*<<< orphan*/  GD_CLOCK_UNDEF ; 
 int /*<<< orphan*/  GD_SPDIF_STATUS_UNDEF ; 
 int check_asic_status (struct echoaudio*) ; 
 int /*<<< orphan*/  clear_handshake (struct echoaudio*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int num_busses_in (struct echoaudio*) ; 
 int num_busses_out (struct echoaudio*) ; 
 int num_pipes_out (struct echoaudio*) ; 
 int send_vector (struct echoaudio*,int /*<<< orphan*/ ) ; 
 scalar_t__ set_digital_mode (struct echoaudio*,int /*<<< orphan*/ ) ; 
 scalar_t__ set_input_clock (struct echoaudio*,int /*<<< orphan*/ ) ; 
 int set_input_gain (struct echoaudio*,int,int /*<<< orphan*/ ) ; 
 int set_monitor_gain (struct echoaudio*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ set_output_clock (struct echoaudio*,int /*<<< orphan*/ ) ; 
 int set_output_gain (struct echoaudio*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ set_phantom_power (struct echoaudio*,int /*<<< orphan*/ ) ; 
 scalar_t__ set_professional_spdif (struct echoaudio*,int /*<<< orphan*/ ) ; 
 int set_sample_rate (struct echoaudio*,int /*<<< orphan*/ ) ; 
 int set_vmixer_gain (struct echoaudio*,int,int,int /*<<< orphan*/ ) ; 
 int update_input_line_level (struct echoaudio*) ; 
 int update_output_line_level (struct echoaudio*) ; 
 scalar_t__ update_vmixer_level (struct echoaudio*) ; 
 scalar_t__ wait_handshake (struct echoaudio*) ; 

__attribute__((used)) static int restore_dsp_rettings(struct echoaudio *chip)
{
	int i, o, err;

	if ((err = check_asic_status(chip)) < 0)
		return err;

	/* Gina20/Darla20 only. Should be harmless for other cards. */
	chip->comm_page->gd_clock_state = GD_CLOCK_UNDEF;
	chip->comm_page->gd_spdif_status = GD_SPDIF_STATUS_UNDEF;
	chip->comm_page->handshake = cpu_to_le32(0xffffffff);

	/* Restore output busses */
	for (i = 0; i < num_busses_out(chip); i++) {
		err = set_output_gain(chip, i, chip->output_gain[i]);
		if (err < 0)
			return err;
	}

#ifdef ECHOCARD_HAS_VMIXER
	for (i = 0; i < num_pipes_out(chip); i++)
		for (o = 0; o < num_busses_out(chip); o++) {
			err = set_vmixer_gain(chip, o, i,
						chip->vmixer_gain[o][i]);
			if (err < 0)
				return err;
		}
	if (update_vmixer_level(chip) < 0)
		return -EIO;
#endif /* ECHOCARD_HAS_VMIXER */

#ifdef ECHOCARD_HAS_MONITOR
	for (o = 0; o < num_busses_out(chip); o++)
		for (i = 0; i < num_busses_in(chip); i++) {
			err = set_monitor_gain(chip, o, i,
						chip->monitor_gain[o][i]);
			if (err < 0)
				return err;
		}
#endif /* ECHOCARD_HAS_MONITOR */

#ifdef ECHOCARD_HAS_INPUT_GAIN
	for (i = 0; i < num_busses_in(chip); i++) {
		err = set_input_gain(chip, i, chip->input_gain[i]);
		if (err < 0)
			return err;
	}
#endif /* ECHOCARD_HAS_INPUT_GAIN */

	err = update_output_line_level(chip);
	if (err < 0)
		return err;

	err = update_input_line_level(chip);
	if (err < 0)
		return err;

	err = set_sample_rate(chip, chip->sample_rate);
	if (err < 0)
		return err;

	if (chip->meters_enabled) {
		err = send_vector(chip, DSP_VC_METERS_ON);
		if (err < 0)
			return err;
	}

#ifdef ECHOCARD_HAS_DIGITAL_MODE_SWITCH
	if (set_digital_mode(chip, chip->digital_mode) < 0)
		return -EIO;
#endif

#ifdef ECHOCARD_HAS_DIGITAL_IO
	if (set_professional_spdif(chip, chip->professional_spdif) < 0)
		return -EIO;
#endif

#ifdef ECHOCARD_HAS_PHANTOM_POWER
	if (set_phantom_power(chip, chip->phantom_power) < 0)
		return -EIO;
#endif

#ifdef ECHOCARD_HAS_EXTERNAL_CLOCK
	/* set_input_clock() also restores automute setting */
	if (set_input_clock(chip, chip->input_clock) < 0)
		return -EIO;
#endif

#ifdef ECHOCARD_HAS_OUTPUT_CLOCK_SWITCH
	if (set_output_clock(chip, chip->output_clock) < 0)
		return -EIO;
#endif

	if (wait_handshake(chip) < 0)
		return -EIO;
	clear_handshake(chip);
	if (send_vector(chip, DSP_VC_UPDATE_FLAGS) < 0)
		return -EIO;

	return 0;
}