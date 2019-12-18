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
struct config {int sleep; int load; int sleep_step; int load_step; int cycles; int rounds; int /*<<< orphan*/  output; int /*<<< orphan*/  governor; scalar_t__ verbose; int /*<<< orphan*/  prio; scalar_t__ cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_CONFIG_FILE ; 
 int /*<<< orphan*/  SCHED_HIGH ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 struct config* malloc (int) ; 
 scalar_t__ prepare_config (int /*<<< orphan*/ ,struct config*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

struct config *prepare_default_config()
{
	struct config *config = malloc(sizeof(struct config));

	dprintf("loading defaults\n");

	config->sleep = 500000;
	config->load = 500000;
	config->sleep_step = 500000;
	config->load_step = 500000;
	config->cycles = 5;
	config->rounds = 50;
	config->cpu = 0;
	config->prio = SCHED_HIGH;
	config->verbose = 0;
	strncpy(config->governor, "ondemand", sizeof(config->governor));

	config->output = stdout;

#ifdef DEFAULT_CONFIG_FILE
	if (prepare_config(DEFAULT_CONFIG_FILE, config))
		return NULL;
#endif
	return config;
}