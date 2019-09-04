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
typedef  int /*<<< orphan*/  u16 ;
struct firmware {scalar_t__ data; } ;
struct echoaudio {int /*<<< orphan*/  dsp_code_to_load; int /*<<< orphan*/ * dsp_code; int /*<<< orphan*/  comm_page; } ;

/* Variables and functions */
 int EPERM ; 
 int check_asic_status (struct echoaudio*) ; 
 int /*<<< orphan*/  free_firmware (struct firmware const*,struct echoaudio*) ; 
 int get_firmware (struct firmware const**,struct echoaudio*,int /*<<< orphan*/ ) ; 
 int load_asic (struct echoaudio*) ; 
 int load_dsp (struct echoaudio*,int /*<<< orphan*/ *) ; 
 scalar_t__ snd_BUG_ON (int) ; 

__attribute__((used)) static int load_firmware(struct echoaudio *chip)
{
	const struct firmware *fw;
	int box_type, err;

	if (snd_BUG_ON(!chip->comm_page))
		return -EPERM;

	/* See if the ASIC is present and working - only if the DSP is already loaded */
	if (chip->dsp_code) {
		if ((box_type = check_asic_status(chip)) >= 0)
			return box_type;
		/* ASIC check failed; force the DSP to reload */
		chip->dsp_code = NULL;
	}

	err = get_firmware(&fw, chip, chip->dsp_code_to_load);
	if (err < 0)
		return err;
	err = load_dsp(chip, (u16 *)fw->data);
	free_firmware(fw, chip);
	if (err < 0)
		return err;

	if ((box_type = load_asic(chip)) < 0)
		return box_type;	/* error */

	return box_type;
}