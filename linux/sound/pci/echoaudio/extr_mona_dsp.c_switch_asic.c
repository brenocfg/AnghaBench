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
struct echoaudio {scalar_t__ device_id; short asic_code; } ;

/* Variables and functions */
 scalar_t__ DEVICE_ID_56361 ; 
 int /*<<< orphan*/  DSP_FNC_LOAD_MONA_PCI_CARD_ASIC ; 
 short FW_MONA_301_1_ASIC48 ; 
 short FW_MONA_301_1_ASIC96 ; 
 short FW_MONA_361_1_ASIC48 ; 
 short FW_MONA_361_1_ASIC96 ; 
 int load_asic_generic (struct echoaudio*,int /*<<< orphan*/ ,short) ; 

__attribute__((used)) static int switch_asic(struct echoaudio *chip, char double_speed)
{
	int err;
	short asic;

	/* Check the clock detect bits to see if this is
	a single-speed clock or a double-speed clock; load
	a new ASIC if necessary. */
	if (chip->device_id == DEVICE_ID_56361) {
		if (double_speed)
			asic = FW_MONA_361_1_ASIC96;
		else
			asic = FW_MONA_361_1_ASIC48;
	} else {
		if (double_speed)
			asic = FW_MONA_301_1_ASIC96;
		else
			asic = FW_MONA_301_1_ASIC48;
	}

	if (asic != chip->asic_code) {
		/* Load the desired ASIC */
		err = load_asic_generic(chip, DSP_FNC_LOAD_MONA_PCI_CARD_ASIC,
					asic);
		if (err < 0)
			return err;
		chip->asic_code = asic;
	}

	return 0;
}