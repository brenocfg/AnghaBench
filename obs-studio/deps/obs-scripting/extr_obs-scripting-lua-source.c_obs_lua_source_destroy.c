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
struct obs_lua_source {int /*<<< orphan*/  definition_mutex; int /*<<< orphan*/  script; } ;
struct obs_lua_data {struct obs_lua_data** p_prev_next; struct obs_lua_data* next; struct obs_lua_source* ls; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (void*) ; 
 int /*<<< orphan*/  call_destroy (struct obs_lua_data*) ; 
 int /*<<< orphan*/  destroy ; 
 int /*<<< orphan*/  have_func (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_script () ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_script () ; 

__attribute__((used)) static void obs_lua_source_destroy(void *data)
{
	struct obs_lua_data *ld = data;
	struct obs_lua_source *ls = ld->ls;
	struct obs_lua_data *next;

	pthread_mutex_lock(&ls->definition_mutex);
	if (!ls->script)
		goto fail;
	if (!have_func(destroy))
		goto fail;

	lock_script();
	call_destroy(ld);
	unlock_script();

fail:
	next = ld->next;
	*ld->p_prev_next = next;
	if (next)
		next->p_prev_next = ld->p_prev_next;

	bfree(data);
	pthread_mutex_unlock(&ls->definition_mutex);
}