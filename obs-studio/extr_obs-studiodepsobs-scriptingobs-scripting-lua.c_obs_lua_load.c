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
struct dstr {int /*<<< orphan*/  array; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  pthread_mutexattr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTHREAD_MUTEX_RECURSIVE ; 
 int /*<<< orphan*/  SCRIPT_DIR ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_printf (struct dstr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_source_def_mutex ; 
 int /*<<< orphan*/  lua_tick ; 
 int /*<<< orphan*/  obs_add_tick_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutexattr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutexattr_settype (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  startup_script ; 
 int /*<<< orphan*/  startup_script_template ; 
 int /*<<< orphan*/  tick_mutex ; 
 int /*<<< orphan*/  timer_mutex ; 

void obs_lua_load(void)
{
	struct dstr dep_paths = {0};
	struct dstr tmp = {0};

	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

	pthread_mutex_init(&tick_mutex, NULL);
	pthread_mutex_init(&timer_mutex, &attr);
	pthread_mutex_init(&lua_source_def_mutex, NULL);

	/* ---------------------------------------------- */
	/* Initialize Lua startup script                  */

	dstr_printf(&tmp, startup_script_template, SCRIPT_DIR);
	startup_script = tmp.array;

	dstr_free(&dep_paths);

	obs_add_tick_callback(lua_tick, NULL);
}