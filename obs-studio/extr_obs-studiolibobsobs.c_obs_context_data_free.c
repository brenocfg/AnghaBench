#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t num; int /*<<< orphan*/ * array; } ;
struct obs_context_data {TYPE_1__ rename_cache; int /*<<< orphan*/  name; int /*<<< orphan*/  rename_cache_mutex; int /*<<< orphan*/  settings; int /*<<< orphan*/  procs; int /*<<< orphan*/  signals; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da_free (TYPE_1__) ; 
 int /*<<< orphan*/  memset (struct obs_context_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  obs_context_data_remove (struct obs_context_data*) ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_hotkeys_context_release (struct obs_context_data*) ; 
 int /*<<< orphan*/  proc_handler_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_handler_destroy (int /*<<< orphan*/ ) ; 

void obs_context_data_free(struct obs_context_data *context)
{
	obs_hotkeys_context_release(context);
	signal_handler_destroy(context->signals);
	proc_handler_destroy(context->procs);
	obs_data_release(context->settings);
	obs_context_data_remove(context);
	pthread_mutex_destroy(&context->rename_cache_mutex);
	bfree(context->name);

	for (size_t i = 0; i < context->rename_cache.num; i++)
		bfree(context->rename_cache.array[i]);
	da_free(context->rename_cache);

	memset(context, 0, sizeof(*context));
}