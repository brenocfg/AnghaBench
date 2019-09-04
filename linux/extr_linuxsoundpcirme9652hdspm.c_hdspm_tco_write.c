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
struct hdspm {TYPE_1__* tco; } ;
struct TYPE_2__ {int input; int framerate; int wordclock; int samplerate; int pull; int term; } ;

/* Variables and functions */
 unsigned int HDSPM_TCO1_LTC_Format_LSB ; 
 unsigned int HDSPM_TCO1_LTC_Format_MSB ; 
 unsigned int HDSPM_TCO1_set_drop_frame_flag ; 
 unsigned int HDSPM_TCO2_WCK_IO_ratio_LSB ; 
 unsigned int HDSPM_TCO2_WCK_IO_ratio_MSB ; 
 unsigned int HDSPM_TCO2_set_01_4 ; 
 unsigned int HDSPM_TCO2_set_freq ; 
 unsigned int HDSPM_TCO2_set_freq_from_app ; 
 unsigned int HDSPM_TCO2_set_input_LSB ; 
 unsigned int HDSPM_TCO2_set_input_MSB ; 
 unsigned int HDSPM_TCO2_set_pull_down ; 
 unsigned int HDSPM_TCO2_set_pull_up ; 
 unsigned int HDSPM_TCO2_set_term_75R ; 
 scalar_t__ HDSPM_WR_TCO ; 
 int /*<<< orphan*/  hdspm_write (struct hdspm*,scalar_t__,unsigned int) ; 

__attribute__((used)) static void hdspm_tco_write(struct hdspm *hdspm)
{
	unsigned int tc[4] = { 0, 0, 0, 0};

	switch (hdspm->tco->input) {
	case 0:
		tc[2] |= HDSPM_TCO2_set_input_MSB;
		break;
	case 1:
		tc[2] |= HDSPM_TCO2_set_input_LSB;
		break;
	default:
		break;
	}

	switch (hdspm->tco->framerate) {
	case 1:
		tc[1] |= HDSPM_TCO1_LTC_Format_LSB;
		break;
	case 2:
		tc[1] |= HDSPM_TCO1_LTC_Format_MSB;
		break;
	case 3:
		tc[1] |= HDSPM_TCO1_LTC_Format_MSB +
			HDSPM_TCO1_set_drop_frame_flag;
		break;
	case 4:
		tc[1] |= HDSPM_TCO1_LTC_Format_LSB +
			HDSPM_TCO1_LTC_Format_MSB;
		break;
	case 5:
		tc[1] |= HDSPM_TCO1_LTC_Format_LSB +
			HDSPM_TCO1_LTC_Format_MSB +
			HDSPM_TCO1_set_drop_frame_flag;
		break;
	default:
		break;
	}

	switch (hdspm->tco->wordclock) {
	case 1:
		tc[2] |= HDSPM_TCO2_WCK_IO_ratio_LSB;
		break;
	case 2:
		tc[2] |= HDSPM_TCO2_WCK_IO_ratio_MSB;
		break;
	default:
		break;
	}

	switch (hdspm->tco->samplerate) {
	case 1:
		tc[2] |= HDSPM_TCO2_set_freq;
		break;
	case 2:
		tc[2] |= HDSPM_TCO2_set_freq_from_app;
		break;
	default:
		break;
	}

	switch (hdspm->tco->pull) {
	case 1:
		tc[2] |= HDSPM_TCO2_set_pull_up;
		break;
	case 2:
		tc[2] |= HDSPM_TCO2_set_pull_down;
		break;
	case 3:
		tc[2] |= HDSPM_TCO2_set_pull_up + HDSPM_TCO2_set_01_4;
		break;
	case 4:
		tc[2] |= HDSPM_TCO2_set_pull_down + HDSPM_TCO2_set_01_4;
		break;
	default:
		break;
	}

	if (1 == hdspm->tco->term) {
		tc[2] |= HDSPM_TCO2_set_term_75R;
	}

	hdspm_write(hdspm, HDSPM_WR_TCO, tc[0]);
	hdspm_write(hdspm, HDSPM_WR_TCO+4, tc[1]);
	hdspm_write(hdspm, HDSPM_WR_TCO+8, tc[2]);
	hdspm_write(hdspm, HDSPM_WR_TCO+12, tc[3]);
}