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
struct config {scalar_t__ verbose; } ;

/* Variables and functions */
 unsigned int GAUGECOUNT ; 
 int /*<<< orphan*/  ROUNDS (unsigned int) ; 
 int /*<<< orphan*/  dprintf (char*,unsigned int) ; 
 long long get_time () ; 
 int /*<<< orphan*/  printf (char*,...) ; 

unsigned int calculate_timespace(long load, struct config *config)
{
	int i;
	long long now, then;
	unsigned int estimated = GAUGECOUNT;
	unsigned int rounds = 0;
	unsigned int timed = 0;

	if (config->verbose)
		printf("calibrating load of %lius, please wait...\n", load);

	/* get the initial calculation time for a specific number of rounds */
	now = get_time();
	ROUNDS(estimated);
	then = get_time();

	timed = (unsigned int)(then - now);

	/* approximation of the wanted load time by comparing with the
	 * initial calculation time */
	for (i = 0; i < 4; i++) {
		rounds = (unsigned int)(load * estimated / timed);
		dprintf("calibrating with %u rounds\n", rounds);
		now = get_time();
		ROUNDS(rounds);
		then = get_time();

		timed = (unsigned int)(then - now);
		estimated = rounds;
	}
	if (config->verbose)
		printf("calibration done\n");

	return estimated;
}