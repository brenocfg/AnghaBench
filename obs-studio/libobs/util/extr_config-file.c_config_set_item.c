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
struct darray {size_t num; struct config_section* array; } ;
struct config_section {char* value; void* name; struct darray items; } ;
struct config_item {char* value; void* name; struct darray items; } ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ config_t ;

/* Variables and functions */
 scalar_t__ astrcmpi (void*,char const*) ; 
 int /*<<< orphan*/  bfree (char*) ; 
 void* bstrdup (char const*) ; 
 void* darray_push_back_new (int,struct darray*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void config_set_item(config_t *config, struct darray *sections,
			    const char *section, const char *name, char *value)
{
	struct config_section *sec = NULL;
	struct config_section *array = sections->array;
	struct config_item *item;
	size_t i, j;

	pthread_mutex_lock(&config->mutex);

	for (i = 0; i < sections->num; i++) {
		struct config_section *cur_sec = array + i;
		struct config_item *items = cur_sec->items.array;

		if (astrcmpi(cur_sec->name, section) == 0) {
			for (j = 0; j < cur_sec->items.num; j++) {
				item = items + j;

				if (astrcmpi(item->name, name) == 0) {
					bfree(item->value);
					item->value = value;
					goto unlock;
				}
			}

			sec = cur_sec;
			break;
		}
	}

	if (!sec) {
		sec = darray_push_back_new(sizeof(struct config_section),
					   sections);
		sec->name = bstrdup(section);
	}

	item = darray_push_back_new(sizeof(struct config_item), &sec->items);
	item->name = bstrdup(name);
	item->value = value;

unlock:
	pthread_mutex_unlock(&config->mutex);
}