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
typedef  scalar_t__ u32 ;
struct echoaudio {int asic_loaded; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ASIC_ALREADY_LOADED ; 
 int /*<<< orphan*/  DSP_VC_TEST_ASIC ; 
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ read_dsp (struct echoaudio*,scalar_t__*) ; 
 int /*<<< orphan*/  send_vector (struct echoaudio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_asic_status(struct echoaudio *chip)
{
	u32 asic_status;

	send_vector(chip, DSP_VC_TEST_ASIC);

	/* The DSP will return a value to indicate whether or not the
	   ASIC is currently loaded */
	if (read_dsp(chip, &asic_status) < 0) {
		dev_err(chip->card->dev,
			"check_asic_status: failed on read_dsp\n");
		chip->asic_loaded = false;
		return -EIO;
	}

	chip->asic_loaded = (asic_status == ASIC_ALREADY_LOADED);
	return chip->asic_loaded ? 0 : -EIO;
}