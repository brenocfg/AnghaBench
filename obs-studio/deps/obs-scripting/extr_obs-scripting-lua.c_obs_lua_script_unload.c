#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct obs_lua_script {int /*<<< orphan*/  mutex; scalar_t__ first_callback; struct obs_lua_script* next_tick; struct obs_lua_script** p_prev_next_tick; int /*<<< orphan*/ * script; } ;
struct TYPE_4__ {scalar_t__ next; } ;
struct lua_obs_callback {TYPE_1__ base; } ;
struct TYPE_5__ {int loaded; } ;
typedef  TYPE_2__ obs_script_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  lua_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_lua_obs_callback (struct lua_obs_callback*) ; 
 int /*<<< orphan*/  tick_mutex ; 
 int /*<<< orphan*/  undef_lua_script_sources (struct obs_lua_script*) ; 

void obs_lua_script_unload(obs_script_t *s)
{
	struct obs_lua_script *data = (struct obs_lua_script *)s;

	if (!s->loaded)
		return;

	lua_State *script = data->script;

	/* ---------------------------- */
	/* undefine source types        */

	undef_lua_script_sources(data);

	/* ---------------------------- */
	/* unhook tick function         */

	if (data->p_prev_next_tick) {
		pthread_mutex_lock(&tick_mutex);

		struct obs_lua_script *next = data->next_tick;
		if (next)
			next->p_prev_next_tick = data->p_prev_next_tick;
		*data->p_prev_next_tick = next;

		pthread_mutex_unlock(&tick_mutex);

		data->p_prev_next_tick = NULL;
		data->next_tick = NULL;
	}

	/* ---------------------------- */
	/* call script_unload           */

	pthread_mutex_lock(&data->mutex);

	lua_getglobal(script, "script_unload");
	lua_pcall(script, 0, 0, 0);

	/* ---------------------------- */
	/* remove all callbacks         */

	struct lua_obs_callback *cb =
		(struct lua_obs_callback *)data->first_callback;
	while (cb) {
		struct lua_obs_callback *next =
			(struct lua_obs_callback *)cb->base.next;
		remove_lua_obs_callback(cb);
		cb = next;
	}

	pthread_mutex_unlock(&data->mutex);

	/* ---------------------------- */
	/* close script                 */

	lua_close(script);
	s->loaded = false;
}