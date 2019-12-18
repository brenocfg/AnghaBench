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
struct obs_context_data {int private; int type; void* hotkey_data; void* settings; int /*<<< orphan*/  name; int /*<<< orphan*/  procs; int /*<<< orphan*/  signals; int /*<<< orphan*/  rename_cache_mutex; } ;
typedef  int /*<<< orphan*/  obs_data_t ;
typedef  enum obs_obj_type { ____Placeholder_obs_obj_type } obs_obj_type ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct obs_context_data*) ; 
 int /*<<< orphan*/  dup_name (char const*,int) ; 
 int /*<<< orphan*/  memset (struct obs_context_data*,int /*<<< orphan*/ ,int) ; 
 void* obs_data_newref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_handler_create () ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_handler_create () ; 

__attribute__((used)) static inline bool obs_context_data_init_wrap(struct obs_context_data *context,
					      enum obs_obj_type type,
					      obs_data_t *settings,
					      const char *name,
					      obs_data_t *hotkey_data,
					      bool private)
{
	assert(context);
	memset(context, 0, sizeof(*context));
	context->private = private;
	context->type = type;

	pthread_mutex_init_value(&context->rename_cache_mutex);
	if (pthread_mutex_init(&context->rename_cache_mutex, NULL) < 0)
		return false;

	context->signals = signal_handler_create();
	if (!context->signals)
		return false;

	context->procs = proc_handler_create();
	if (!context->procs)
		return false;

	context->name = dup_name(name, private);
	context->settings = obs_data_newref(settings);
	context->hotkey_data = obs_data_newref(hotkey_data);
	return true;
}