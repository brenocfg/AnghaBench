#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  filter_mutex; } ;
typedef  TYPE_1__ obs_source_t ;
typedef  enum obs_order_movement { ____Placeholder_obs_order_movement } obs_order_movement ;

/* Variables and functions */
 int move_filter_dir (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  obs_ptr_valid (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  obs_source_dosignal (TYPE_1__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_source_valid (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void obs_source_filter_set_order(obs_source_t *source, obs_source_t *filter,
				 enum obs_order_movement movement)
{
	bool success;

	if (!obs_source_valid(source, "obs_source_filter_set_order"))
		return;
	if (!obs_ptr_valid(filter, "obs_source_filter_set_order"))
		return;

	pthread_mutex_lock(&source->filter_mutex);
	success = move_filter_dir(source, filter, movement);
	pthread_mutex_unlock(&source->filter_mutex);

	if (success)
		obs_source_dosignal(source, NULL, "reorder_filters");
}