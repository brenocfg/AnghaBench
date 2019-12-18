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
struct efc_clock {unsigned int source; unsigned int sampling_rate; unsigned int index; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  EFC_CAT_HWCTL ; 
 int /*<<< orphan*/  EFC_CMD_HWCTL_SET_CLOCK ; 
 int EINVAL ; 
 unsigned int UINT_MAX ; 
 int command_get_clock (struct snd_efw*,struct efc_clock*) ; 
 int /*<<< orphan*/  cpu_to_be32s (unsigned int*) ; 
 int efw_transaction (struct snd_efw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int
command_set_clock(struct snd_efw *efw,
		  unsigned int source, unsigned int rate)
{
	struct efc_clock clock = {0};
	int err;

	/* check arguments */
	if ((source == UINT_MAX) && (rate == UINT_MAX)) {
		err = -EINVAL;
		goto end;
	}

	/* get current status */
	err = command_get_clock(efw, &clock);
	if (err < 0)
		goto end;

	/* no need */
	if ((clock.source == source) && (clock.sampling_rate == rate))
		goto end;

	/* set params */
	if ((source != UINT_MAX) && (clock.source != source))
		clock.source = source;
	if ((rate != UINT_MAX) && (clock.sampling_rate != rate))
		clock.sampling_rate = rate;
	clock.index = 0;

	cpu_to_be32s(&clock.source);
	cpu_to_be32s(&clock.sampling_rate);
	cpu_to_be32s(&clock.index);

	err = efw_transaction(efw, EFC_CAT_HWCTL,
			      EFC_CMD_HWCTL_SET_CLOCK,
			      (__be32 *)&clock, sizeof(struct efc_clock),
			      NULL, 0);
	if (err < 0)
		goto end;

	/*
	 * With firmware version 5.8, just after changing clock state, these
	 * parameters are not immediately retrieved by get command. In my
	 * trial, there needs to be 100msec to get changed parameters.
	 */
	msleep(150);
end:
	return err;
}