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
struct oxygen {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dg_controls ; 
 int /*<<< orphan*/  input_source_apply (struct oxygen*) ; 
 int /*<<< orphan*/  output_select_apply (struct oxygen*) ; 
 int /*<<< orphan*/  oxygen_update_dac_routing (struct oxygen*) ; 
 int snd_ctl_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,struct oxygen*) ; 

__attribute__((used)) static int dg_mixer_init(struct oxygen *chip)
{
	unsigned int i;
	int err;

	output_select_apply(chip);
	input_source_apply(chip);
	oxygen_update_dac_routing(chip);

	for (i = 0; i < ARRAY_SIZE(dg_controls); ++i) {
		err = snd_ctl_add(chip->card,
				  snd_ctl_new1(&dg_controls[i], chip));
		if (err < 0)
			return err;
	}

	return 0;
}