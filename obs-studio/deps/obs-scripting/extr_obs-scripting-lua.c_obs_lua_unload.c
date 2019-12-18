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

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_source_def_mutex ; 
 int /*<<< orphan*/  lua_tick ; 
 int /*<<< orphan*/  obs_remove_tick_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  startup_script ; 
 int /*<<< orphan*/  tick_mutex ; 
 int /*<<< orphan*/  timer_mutex ; 

void obs_lua_unload(void)
{
	obs_remove_tick_callback(lua_tick, NULL);

	bfree(startup_script);
	pthread_mutex_destroy(&tick_mutex);
	pthread_mutex_destroy(&timer_mutex);
	pthread_mutex_destroy(&lua_source_def_mutex);
}