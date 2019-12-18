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
struct echoaudio {int /*<<< orphan*/ * dsp_code; int /*<<< orphan*/  active_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSP_VC_GO_COMATOSE ; 
 int /*<<< orphan*/  enable_midi_input (struct echoaudio*,int) ; 
 int send_vector (struct echoaudio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_meters_on (struct echoaudio*,int) ; 
 int /*<<< orphan*/  stop_transport (struct echoaudio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rest_in_peace(struct echoaudio *chip)
{

	/* Stops all active pipes (just to be sure) */
	stop_transport(chip, chip->active_mask);

	set_meters_on(chip, false);

#ifdef ECHOCARD_HAS_MIDI
	enable_midi_input(chip, false);
#endif

	/* Go to sleep */
	if (chip->dsp_code) {
		/* Make load_firmware do a complete reload */
		chip->dsp_code = NULL;
		/* Put the DSP to sleep */
		return send_vector(chip, DSP_VC_GO_COMATOSE);
	}
	return 0;
}