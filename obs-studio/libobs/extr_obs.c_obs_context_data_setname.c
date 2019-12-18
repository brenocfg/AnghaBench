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
struct obs_context_data {int /*<<< orphan*/  rename_cache_mutex; int /*<<< orphan*/  private; scalar_t__ name; int /*<<< orphan*/  rename_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ dup_name (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void obs_context_data_setname(struct obs_context_data *context,
			      const char *name)
{
	pthread_mutex_lock(&context->rename_cache_mutex);

	if (context->name)
		da_push_back(context->rename_cache, &context->name);
	context->name = dup_name(name, context->private);

	pthread_mutex_unlock(&context->rename_cache_mutex);
}