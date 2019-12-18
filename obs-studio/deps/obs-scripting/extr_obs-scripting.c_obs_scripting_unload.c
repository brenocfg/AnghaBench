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
struct script_callback {struct script_callback* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  circlebuf_free (int /*<<< orphan*/ *) ; 
 int defer_call_exit ; 
 int /*<<< orphan*/  defer_call_mutex ; 
 int /*<<< orphan*/  defer_call_queue ; 
 int /*<<< orphan*/  defer_call_semaphore ; 
 int /*<<< orphan*/  defer_call_thread ; 
 int /*<<< orphan*/  detach_mutex ; 
 struct script_callback* detached_callbacks ; 
 int /*<<< orphan*/  dstr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_filter ; 
 int /*<<< orphan*/  just_free_script_callback (struct script_callback*) ; 
 int /*<<< orphan*/  obs_lua_unload () ; 
 int /*<<< orphan*/  obs_python_unload () ; 
 int /*<<< orphan*/  os_sem_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_sem_post (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int scripting_loaded ; 

void obs_scripting_unload(void)
{
	if (!scripting_loaded)
		return;

		/* ---------------------- */

#if COMPILE_LUA
	obs_lua_unload();
#endif

#if COMPILE_PYTHON
	obs_python_unload();
#endif

	dstr_free(&file_filter);

	/* ---------------------- */

	int total_detached = 0;

	pthread_mutex_lock(&detach_mutex);

	struct script_callback *cur = detached_callbacks;
	while (cur) {
		struct script_callback *next = cur->next;
		just_free_script_callback(cur);
		cur = next;

		++total_detached;
	}

	pthread_mutex_unlock(&detach_mutex);
	pthread_mutex_destroy(&detach_mutex);

	blog(LOG_INFO, "[Scripting] Total detached callbacks: %d",
	     total_detached);

	/* ---------------------- */

	pthread_mutex_lock(&defer_call_mutex);

	/* TODO */

	defer_call_exit = true;
	circlebuf_free(&defer_call_queue);

	pthread_mutex_unlock(&defer_call_mutex);

	os_sem_post(defer_call_semaphore);
	pthread_join(defer_call_thread, NULL);

	pthread_mutex_destroy(&defer_call_mutex);
	os_sem_destroy(defer_call_semaphore);

	scripting_loaded = false;
}