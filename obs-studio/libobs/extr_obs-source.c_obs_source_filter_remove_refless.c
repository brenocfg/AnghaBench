#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct calldata {int dummy; } ;
typedef  int /*<<< orphan*/  stack ;
struct TYPE_11__ {int /*<<< orphan*/  data; int /*<<< orphan*/  name; int /*<<< orphan*/  signals; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* filter_remove ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  id; } ;
struct TYPE_13__ {TYPE_3__** array; } ;
struct TYPE_12__ {int /*<<< orphan*/ * filter_target; int /*<<< orphan*/ * filter_parent; TYPE_2__ context; TYPE_1__ info; int /*<<< orphan*/  filter_mutex; TYPE_6__ filters; } ;
typedef  TYPE_3__ obs_source_t ;

/* Variables and functions */
 size_t DARRAY_INVALID ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calldata_init_fixed (struct calldata*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  calldata_set_ptr (struct calldata*,char*,TYPE_3__*) ; 
 int /*<<< orphan*/  da_erase (TYPE_6__,size_t) ; 
 size_t da_find (TYPE_6__,TYPE_3__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_handler_signal (int /*<<< orphan*/ ,char*,struct calldata*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool obs_source_filter_remove_refless(obs_source_t *source,
					     obs_source_t *filter)
{
	struct calldata cd;
	uint8_t stack[128];
	size_t idx;

	pthread_mutex_lock(&source->filter_mutex);

	idx = da_find(source->filters, &filter, 0);
	if (idx == DARRAY_INVALID) {
		pthread_mutex_unlock(&source->filter_mutex);
		return false;
	}

	if (idx > 0) {
		obs_source_t *prev = source->filters.array[idx - 1];
		prev->filter_target = filter->filter_target;
	}

	da_erase(source->filters, idx);

	pthread_mutex_unlock(&source->filter_mutex);

	calldata_init_fixed(&cd, stack, sizeof(stack));
	calldata_set_ptr(&cd, "source", source);
	calldata_set_ptr(&cd, "filter", filter);

	signal_handler_signal(source->context.signals, "filter_remove", &cd);

	blog(LOG_DEBUG, "- filter '%s' (%s) removed from source '%s'",
	     filter->context.name, filter->info.id, source->context.name);

	if (filter->info.filter_remove)
		filter->info.filter_remove(filter->context.data,
					   filter->filter_parent);

	filter->filter_parent = NULL;
	filter->filter_target = NULL;
	return true;
}