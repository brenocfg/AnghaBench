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
typedef  int u32 ;
struct echoaudio {scalar_t__ device_id; short asic_code; scalar_t__ asic_loaded; } ;

/* Variables and functions */
 scalar_t__ DEVICE_ID_56361 ; 
 int /*<<< orphan*/  DSP_FNC_LOAD_GINA24_ASIC ; 
 short FW_GINA24_301_ASIC ; 
 short FW_GINA24_361_ASIC ; 
 int GML_48KHZ ; 
 int GML_CONVERTER_ENABLE ; 
 int check_asic_status (struct echoaudio*) ; 
 int load_asic_generic (struct echoaudio*,int /*<<< orphan*/ ,short) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int write_control_reg (struct echoaudio*,int,int) ; 

__attribute__((used)) static int load_asic(struct echoaudio *chip)
{
	u32 control_reg;
	int err;
	short asic;

	if (chip->asic_loaded)
		return 1;

	/* Give the DSP a few milliseconds to settle down */
	mdelay(10);

	/* Pick the correct ASIC for '301 or '361 Gina24 */
	if (chip->device_id == DEVICE_ID_56361)
		asic = FW_GINA24_361_ASIC;
	else
		asic = FW_GINA24_301_ASIC;

	err = load_asic_generic(chip, DSP_FNC_LOAD_GINA24_ASIC, asic);
	if (err < 0)
		return err;

	chip->asic_code = asic;

	/* Now give the new ASIC a little time to set up */
	mdelay(10);
	/* See if it worked */
	err = check_asic_status(chip);

	/* Set up the control register if the load succeeded -
	   48 kHz, internal clock, S/PDIF RCA mode */
	if (!err) {
		control_reg = GML_CONVERTER_ENABLE | GML_48KHZ;
		err = write_control_reg(chip, control_reg, true);
	}
	return err;
}