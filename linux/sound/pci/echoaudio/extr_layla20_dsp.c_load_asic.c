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
struct echoaudio {scalar_t__ asic_loaded; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSP_FNC_LOAD_LAYLA_ASIC ; 
 int /*<<< orphan*/  FW_LAYLA20_ASIC ; 
 int check_asic_status (struct echoaudio*) ; 
 int load_asic_generic (struct echoaudio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int load_asic(struct echoaudio *chip)
{
	int err;

	if (chip->asic_loaded)
		return 0;

	err = load_asic_generic(chip, DSP_FNC_LOAD_LAYLA_ASIC,
				FW_LAYLA20_ASIC);
	if (err < 0)
		return err;

	/* Check if ASIC is alive and well. */
	return check_asic_status(chip);
}