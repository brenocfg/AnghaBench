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
struct obs_lua_data {struct obs_lua_source* ls; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_func (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  have_func (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_script () ; 
 int /*<<< orphan*/  ls_push_data () ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_script () ; 
 int /*<<< orphan*/  video_tick ; 

__attribute__((used)) static void obs_lua_source_video_tick(void *data, float seconds)
{
	struct obs_lua_data *ld = data;
	struct obs_lua_source *ls = ld->ls;

	pthread_mutex_lock(&ls->definition_mutex);
	if (!ls->script)
		goto fail;
	if (!have_func(video_tick))
		goto fail;

	lock_script();

	ls_push_data();
	lua_pushnumber(ls->script, (double)seconds);
	call_func(video_tick, 2, 0);

	unlock_script();

fail:
	pthread_mutex_unlock(&ls->definition_mutex);
}