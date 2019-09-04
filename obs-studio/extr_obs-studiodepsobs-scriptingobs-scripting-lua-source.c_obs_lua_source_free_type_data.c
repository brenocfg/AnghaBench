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
struct obs_lua_source {int /*<<< orphan*/  definition_mutex; int /*<<< orphan*/ * script; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct obs_lua_source*) ; 
 int /*<<< orphan*/  lock_script () ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  source_type_unload (struct obs_lua_source*) ; 
 int /*<<< orphan*/  unlock_script () ; 

__attribute__((used)) static void obs_lua_source_free_type_data(void *type_data)
{
	struct obs_lua_source *ls = type_data;

	pthread_mutex_lock(&ls->definition_mutex);

	if (ls->script) {
		lock_script();
		source_type_unload(ls);
		unlock_script();
		ls->script = NULL;
	}

	pthread_mutex_unlock(&ls->definition_mutex);
	pthread_mutex_destroy(&ls->definition_mutex);
	bfree(ls);
}