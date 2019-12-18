#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct script_callback {struct script_callback* next; } ;
struct obs_python_script {struct script_callback* first_callback; int /*<<< orphan*/ * get_properties; int /*<<< orphan*/ * update; int /*<<< orphan*/ * save; int /*<<< orphan*/ * tick; struct obs_python_script* next_tick; struct obs_python_script** p_prev_next_tick; } ;
struct TYPE_3__ {int loaded; } ;
typedef  TYPE_1__ obs_script_t ;

/* Variables and functions */
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_python () ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  python_loaded ; 
 int /*<<< orphan*/  remove_script_callback (struct script_callback*) ; 
 int /*<<< orphan*/  tick_mutex ; 
 int /*<<< orphan*/  unload_python_script (struct obs_python_script*) ; 
 int /*<<< orphan*/  unlock_python () ; 

void obs_python_script_unload(obs_script_t *s)
{
	struct obs_python_script *data = (struct obs_python_script *)s;

	if (!s->loaded || !python_loaded)
		return;

	/* ---------------------------- */
	/* unhook tick function         */

	if (data->p_prev_next_tick) {
		pthread_mutex_lock(&tick_mutex);

		struct obs_python_script *next = data->next_tick;
		if (next)
			next->p_prev_next_tick = data->p_prev_next_tick;
		*data->p_prev_next_tick = next;

		pthread_mutex_unlock(&tick_mutex);

		data->p_prev_next_tick = NULL;
		data->next_tick = NULL;
	}

	lock_python();

	Py_XDECREF(data->tick);
	Py_XDECREF(data->save);
	Py_XDECREF(data->update);
	Py_XDECREF(data->get_properties);
	data->tick = NULL;
	data->save = NULL;
	data->update = NULL;
	data->get_properties = NULL;

	/* ---------------------------- */
	/* remove all callbacks         */

	struct script_callback *cb = data->first_callback;
	while (cb) {
		struct script_callback *next = cb->next;
		remove_script_callback(cb);
		cb = next;
	}

	/* ---------------------------- */
	/* unload                       */

	unload_python_script(data);
	unlock_python();

	s->loaded = false;
}