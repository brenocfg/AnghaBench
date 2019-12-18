#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct config_section {int dummy; } ;
struct TYPE_6__ {size_t num; struct config_section* array; } ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; struct TYPE_5__* file; TYPE_2__ sections; TYPE_2__ defaults; } ;
typedef  TYPE_1__ config_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (TYPE_1__*) ; 
 int /*<<< orphan*/  config_section_free (struct config_section*) ; 
 int /*<<< orphan*/  darray_free (TYPE_2__*) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

void config_close(config_t *config)
{
	struct config_section *defaults, *sections;
	size_t i;

	if (!config)
		return;

	defaults = config->defaults.array;
	sections = config->sections.array;

	for (i = 0; i < config->defaults.num; i++)
		config_section_free(defaults + i);
	for (i = 0; i < config->sections.num; i++)
		config_section_free(sections + i);

	darray_free(&config->defaults);
	darray_free(&config->sections);
	bfree(config->file);
	pthread_mutex_destroy(&config->mutex);
	bfree(config);
}