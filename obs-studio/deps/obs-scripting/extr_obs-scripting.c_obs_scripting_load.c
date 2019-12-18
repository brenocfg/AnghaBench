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
 int /*<<< orphan*/  circlebuf_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  defer_call_mutex ; 
 int /*<<< orphan*/  defer_call_queue ; 
 int /*<<< orphan*/  defer_call_semaphore ; 
 int /*<<< orphan*/  defer_call_thread ; 
 int /*<<< orphan*/  defer_thread ; 
 int /*<<< orphan*/  detach_mutex ; 
 int /*<<< orphan*/  obs_lua_load () ; 
 int /*<<< orphan*/  obs_python_load () ; 
 int /*<<< orphan*/  obs_scripting_load_python (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_sem_destroy (int /*<<< orphan*/ ) ; 
 scalar_t__ os_sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int scripting_loaded ; 

bool obs_scripting_load(void)
{
	circlebuf_init(&defer_call_queue);

	if (pthread_mutex_init(&detach_mutex, NULL) != 0) {
		return false;
	}
	if (pthread_mutex_init(&defer_call_mutex, NULL) != 0) {
		pthread_mutex_destroy(&detach_mutex);
		return false;
	}
	if (os_sem_init(&defer_call_semaphore, 0) != 0) {
		pthread_mutex_destroy(&defer_call_mutex);
		pthread_mutex_destroy(&detach_mutex);
		return false;
	}

	if (pthread_create(&defer_call_thread, NULL, defer_thread, NULL) != 0) {
		os_sem_destroy(defer_call_semaphore);
		pthread_mutex_destroy(&defer_call_mutex);
		pthread_mutex_destroy(&detach_mutex);
		return false;
	}

#if COMPILE_LUA
	obs_lua_load();
#endif

#if COMPILE_PYTHON
	obs_python_load();
#ifndef _WIN32 /* don't risk python startup load issues on windows */
	obs_scripting_load_python(NULL);
#endif
#endif

	scripting_loaded = true;
	return true;
}