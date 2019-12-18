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
 int snd_ctl_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,struct snd_ice1712*) ; 
 int /*<<< orphan*/ * stac9640_controls ; 

__attribute__((used)) static int wtm_add_controls(struct snd_ice1712 *ice)
{
	unsigned int i;
	int err;

	for (i = 0; i < ARRAY_SIZE(stac9640_controls); i++) {
		err = snd_ctl_add(ice->card,
				snd_ctl_new1(&stac9640_controls[i], ice));
		if (err < 0)
			return err;
	}
	return 0;
}