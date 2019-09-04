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
struct xonar_pcm179x {int /*<<< orphan*/  broken_i2c; } ;
struct oxygen {int /*<<< orphan*/  card; struct xonar_pcm179x* model_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  rolloff_control ; 
 int snd_ctl_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,struct oxygen*) ; 

__attribute__((used)) static int add_pcm1796_controls(struct oxygen *chip)
{
	struct xonar_pcm179x *data = chip->model_data;
	int err;

	if (!data->broken_i2c) {
		err = snd_ctl_add(chip->card,
				  snd_ctl_new1(&rolloff_control, chip));
		if (err < 0)
			return err;
	}
	return 0;
}