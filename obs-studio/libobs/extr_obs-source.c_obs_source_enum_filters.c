#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct obs_source {int dummy; } ;
struct TYPE_8__ {size_t num; struct obs_source** array; } ;
struct TYPE_9__ {int /*<<< orphan*/  filter_mutex; TYPE_1__ filters; } ;
typedef  TYPE_2__ obs_source_t ;
typedef  int /*<<< orphan*/  (* obs_source_enum_proc_t ) (TYPE_2__*,struct obs_source*,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  obs_ptr_valid (int /*<<< orphan*/  (*) (TYPE_2__*,struct obs_source*,void*),char*) ; 
 int /*<<< orphan*/  obs_source_valid (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void obs_source_enum_filters(obs_source_t *source,
			     obs_source_enum_proc_t callback, void *param)
{
	if (!obs_source_valid(source, "obs_source_enum_filters"))
		return;
	if (!obs_ptr_valid(callback, "obs_source_enum_filters"))
		return;

	pthread_mutex_lock(&source->filter_mutex);

	for (size_t i = source->filters.num; i > 0; i--) {
		struct obs_source *filter = source->filters.array[i - 1];
		callback(source, filter, param);
	}

	pthread_mutex_unlock(&source->filter_mutex);
}