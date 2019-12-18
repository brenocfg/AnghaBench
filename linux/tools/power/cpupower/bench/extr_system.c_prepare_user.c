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
struct config {unsigned int rounds; int cycles; unsigned int sleep; unsigned int sleep_step; int load; unsigned int load_step; scalar_t__ output; scalar_t__ verbose; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int) ; 
 scalar_t__ stdout ; 

void prepare_user(const struct config *config)
{
	unsigned long sleep_time = 0;
	unsigned long load_time = 0;
	unsigned int round;

	for (round = 0; round < config->rounds; round++) {
		sleep_time +=  2 * config->cycles *
			(config->sleep + config->sleep_step * round);
		load_time += 2 * config->cycles *
			(config->load + config->load_step * round) +
			(config->load + config->load_step * round * 4);
	}

	if (config->verbose || config->output != stdout)
		printf("approx. test duration: %im\n",
		       (int)((sleep_time + load_time) / 60000000));
}