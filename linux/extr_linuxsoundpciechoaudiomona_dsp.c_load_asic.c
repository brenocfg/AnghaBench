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
 int /*<<< orphan*/  DSP_FNC_LOAD_MONA_EXTERNAL_ASIC ; 
 int /*<<< orphan*/  DSP_FNC_LOAD_MONA_PCI_CARD_ASIC ; 
 short FW_MONA_2_ASIC ; 
 short FW_MONA_301_1_ASIC48 ; 
 short FW_MONA_361_1_ASIC48 ; 
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
		return 0;

	mdelay(10);

	if (chip->device_id == DEVICE_ID_56361)
		asic = FW_MONA_361_1_ASIC48;
	else
		asic = FW_MONA_301_1_ASIC48;

	err = load_asic_generic(chip, DSP_FNC_LOAD_MONA_PCI_CARD_ASIC, asic);
	if (err < 0)
		return err;

	chip->asic_code = asic;
	mdelay(10);

	/* Do the external one */
	err = load_asic_generic(chip, DSP_FNC_LOAD_MONA_EXTERNAL_ASIC,
				FW_MONA_2_ASIC);
	if (err < 0)
		return err;

	mdelay(10);
	err = check_asic_status(chip);

	/* Set up the control register if the load succeeded -
	   48 kHz, internal clock, S/PDIF RCA mode */
	if (!err) {
		control_reg = GML_CONVERTER_ENABLE | GML_48KHZ;
		err = write_control_reg(chip, control_reg, true);
	}

	return err;
}