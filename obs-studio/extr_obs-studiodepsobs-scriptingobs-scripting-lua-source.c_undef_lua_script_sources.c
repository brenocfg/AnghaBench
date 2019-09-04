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
struct obs_lua_source {scalar_t__ script; struct obs_lua_source* next; } ;
struct obs_lua_script {scalar_t__ script; } ;

/* Variables and functions */
 struct obs_lua_source* first_source_def ; 
 int /*<<< orphan*/  lua_source_def_mutex ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  undef_source_type (struct obs_lua_script*,struct obs_lua_source*) ; 

void undef_lua_script_sources(struct obs_lua_script *data)
{
	pthread_mutex_lock(&lua_source_def_mutex);

	struct obs_lua_source *def = first_source_def;
	while (def) {
		if (def->script == data->script)
			undef_source_type(data, def);
		def = def->next;
	}

	pthread_mutex_unlock(&lua_source_def_mutex);
}