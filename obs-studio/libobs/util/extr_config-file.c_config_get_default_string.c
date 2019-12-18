#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct config_item {char* value; } ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  defaults; } ;
typedef  TYPE_1__ config_t ;

/* Variables and functions */
 struct config_item* config_find_item (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

const char *config_get_default_string(config_t *config, const char *section,
				      const char *name)
{
	const struct config_item *item;
	const char *value = NULL;

	pthread_mutex_lock(&config->mutex);

	item = config_find_item(&config->defaults, section, name);
	if (item)
		value = item->value;

	pthread_mutex_unlock(&config->mutex);
	return value;
}