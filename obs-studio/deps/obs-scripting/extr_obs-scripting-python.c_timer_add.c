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
typedef  unsigned long long uint64_t ;
struct python_obs_timer {unsigned long long interval; int /*<<< orphan*/  last_ts; } ;
struct python_obs_callback {int dummy; } ;
struct obs_python_script {int dummy; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 struct python_obs_callback* add_python_obs_callback_extra (struct obs_python_script*,int /*<<< orphan*/ *,int) ; 
 struct obs_python_script* cur_python_script ; 
 int /*<<< orphan*/  defer_call_post (int /*<<< orphan*/ ,struct python_obs_callback*) ; 
 int /*<<< orphan*/  defer_timer_init ; 
 int /*<<< orphan*/  obs_get_video_frame_time () ; 
 int /*<<< orphan*/  parse_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/ * python_none () ; 
 struct python_obs_timer* python_obs_callback_extra_data (struct python_obs_callback*) ; 

__attribute__((used)) static PyObject *timer_add(PyObject *self, PyObject *args)
{
	struct obs_python_script *script = cur_python_script;
	PyObject *py_cb;
	int ms;

	UNUSED_PARAMETER(self);

	if (!parse_args(args, "Oi", &py_cb, &ms))
		return python_none();

	struct python_obs_callback *cb = add_python_obs_callback_extra(
		script, py_cb, sizeof(struct python_obs_timer));
	struct python_obs_timer *timer = python_obs_callback_extra_data(cb);

	timer->interval = (uint64_t)ms * 1000000ULL;
	timer->last_ts = obs_get_video_frame_time();

	defer_call_post(defer_timer_init, cb);
	return python_none();
}