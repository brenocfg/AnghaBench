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
struct echoaudio {int sample_rate; int /*<<< orphan*/  output_clock; int /*<<< orphan*/  input_clock; int /*<<< orphan*/  vmixer_gain; int /*<<< orphan*/  monitor_gain; int /*<<< orphan*/  input_gain; int /*<<< orphan*/  output_gain; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECHOGAIN_MUTED ; 
 int /*<<< orphan*/  ECHO_CLOCK_INTERNAL ; 
 int /*<<< orphan*/  ECHO_CLOCK_WORD ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int restore_dsp_rettings (struct echoaudio*) ; 

__attribute__((used)) static int init_line_levels(struct echoaudio *chip)
{
	memset(chip->output_gain, ECHOGAIN_MUTED, sizeof(chip->output_gain));
	memset(chip->input_gain, ECHOGAIN_MUTED, sizeof(chip->input_gain));
	memset(chip->monitor_gain, ECHOGAIN_MUTED, sizeof(chip->monitor_gain));
	memset(chip->vmixer_gain, ECHOGAIN_MUTED, sizeof(chip->vmixer_gain));
	chip->input_clock = ECHO_CLOCK_INTERNAL;
	chip->output_clock = ECHO_CLOCK_WORD;
	chip->sample_rate = 44100;
	return restore_dsp_rettings(chip);
}