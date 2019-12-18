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
struct TYPE_3__ {size_t num; int /*<<< orphan*/ * array; } ;

/* Variables and functions */
 int /*<<< orphan*/  PyGILState_Ensure () ; 
 int /*<<< orphan*/  Py_Finalize () ; 
 scalar_t__ Py_IsInitialized () ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cur_py_log_chunk ; 
 int /*<<< orphan*/  da_free (TYPE_1__) ; 
 int /*<<< orphan*/  dstr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_remove_tick_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  py_obspython ; 
 scalar_t__ python_loaded ; 
 int python_loaded_at_all ; 
 TYPE_1__ python_paths ; 
 int /*<<< orphan*/  python_tick ; 
 int /*<<< orphan*/  tick_mutex ; 
 int /*<<< orphan*/  timer_mutex ; 

void obs_python_unload(void)
{
	if (!python_loaded_at_all)
		return;

	if (python_loaded && Py_IsInitialized()) {
		PyGILState_Ensure();

		Py_XDECREF(py_obspython);
		Py_Finalize();
	}

	/* ---------------------- */

	obs_remove_tick_callback(python_tick, NULL);

	for (size_t i = 0; i < python_paths.num; i++)
		bfree(python_paths.array[i]);
	da_free(python_paths);

	pthread_mutex_destroy(&tick_mutex);
	pthread_mutex_destroy(&timer_mutex);
	dstr_free(&cur_py_log_chunk);

	python_loaded_at_all = false;
}