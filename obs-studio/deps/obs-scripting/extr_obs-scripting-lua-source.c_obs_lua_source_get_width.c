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
typedef  scalar_t__ uint32_t ;
struct obs_lua_source {int /*<<< orphan*/  definition_mutex; int /*<<< orphan*/  script; } ;
struct obs_lua_data {struct obs_lua_source* ls; } ;

/* Variables and functions */
 scalar_t__ call_func (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  get_width ; 
 int /*<<< orphan*/  have_func (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_script () ; 
 int /*<<< orphan*/  ls_pop (int) ; 
 int /*<<< orphan*/  ls_push_data () ; 
 scalar_t__ lua_tointeger (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_script () ; 

__attribute__((used)) static uint32_t obs_lua_source_get_width(void *data)
{
	struct obs_lua_data *ld = data;
	struct obs_lua_source *ls = ld->ls;
	uint32_t width = 0;

	pthread_mutex_lock(&ls->definition_mutex);
	if (!ls->script)
		goto fail;
	if (!have_func(get_width))
		goto fail;

	lock_script();

	ls_push_data();
	if (call_func(get_width, 1, 1)) {
		width = (uint32_t)lua_tointeger(ls->script, -1);
		ls_pop(1);
	}

	unlock_script();

fail:
	pthread_mutex_unlock(&ls->definition_mutex);
	return width;
}