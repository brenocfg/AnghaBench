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
struct snd_efw {int dummy; } ;
struct efc_clock {unsigned int sampling_rate; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int command_get_clock (struct snd_efw*,struct efc_clock*) ; 

int snd_efw_command_get_sampling_rate(struct snd_efw *efw, unsigned int *rate)
{
	int err;
	struct efc_clock clock = {0};

	err = command_get_clock(efw, &clock);
	if (err >= 0)
		*rate = clock.sampling_rate;

	return err;
}