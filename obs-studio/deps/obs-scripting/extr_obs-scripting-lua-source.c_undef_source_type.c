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
struct obs_lua_source {int /*<<< orphan*/  definition_mutex; int /*<<< orphan*/ * script; struct obs_lua_data* first_source; int /*<<< orphan*/  id; } ;
struct obs_lua_script {int /*<<< orphan*/  mutex; } ;
struct obs_lua_data {struct obs_lua_data* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_destroy (struct obs_lua_data*) ; 
 int /*<<< orphan*/  obs_enable_source_type (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  source_type_unload (struct obs_lua_source*) ; 

__attribute__((used)) static inline void undef_source_type(struct obs_lua_script *data,
				     struct obs_lua_source *ls)
{
	pthread_mutex_lock(&ls->definition_mutex);
	pthread_mutex_lock(&data->mutex);

	obs_enable_source_type(ls->id, false);

	struct obs_lua_data *ld = ls->first_source;
	while (ld) {
		call_destroy(ld);
		ld = ld->next;
	}

	source_type_unload(ls);
	ls->script = NULL;

	pthread_mutex_unlock(&data->mutex);
	pthread_mutex_unlock(&ls->definition_mutex);
}