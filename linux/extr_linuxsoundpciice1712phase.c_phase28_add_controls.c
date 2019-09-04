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
struct snd_ice1712 {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * phase28_dac_controls ; 
 int snd_ctl_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,struct snd_ice1712*) ; 
 int /*<<< orphan*/ * wm_controls ; 

__attribute__((used)) static int phase28_add_controls(struct snd_ice1712 *ice)
{
	unsigned int i, counts;
	int err;

	counts = ARRAY_SIZE(phase28_dac_controls);
	for (i = 0; i < counts; i++) {
		err = snd_ctl_add(ice->card,
					snd_ctl_new1(&phase28_dac_controls[i],
							ice));
		if (err < 0)
			return err;
	}

	for (i = 0; i < ARRAY_SIZE(wm_controls); i++) {
		err = snd_ctl_add(ice->card,
					snd_ctl_new1(&wm_controls[i], ice));
		if (err < 0)
			return err;
	}

	return 0;
}