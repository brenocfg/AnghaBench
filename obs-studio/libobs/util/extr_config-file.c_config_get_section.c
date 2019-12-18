#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct config_section {char* name; } ;
struct TYPE_5__ {size_t num; } ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; TYPE_2__ sections; } ;
typedef  TYPE_1__ config_t ;

/* Variables and functions */
 struct config_section* darray_item (int,TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

const char *config_get_section(config_t *config, size_t idx)
{
	struct config_section *section;
	const char *name = NULL;

	pthread_mutex_lock(&config->mutex);

	if (idx >= config->sections.num)
		goto unlock;

	section = darray_item(sizeof(struct config_section), &config->sections,
			      idx);
	name = section->name;

unlock:
	pthread_mutex_unlock(&config->mutex);
	return name;
}