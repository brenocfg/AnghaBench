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
struct script_callback {scalar_t__ removed; } ;
struct python_obs_callback {int /*<<< orphan*/  func; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PyObject_CallObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_callback (struct python_obs_callback*) ; 
 int /*<<< orphan*/  py_error () ; 
 int /*<<< orphan*/  unlock_callback () ; 

__attribute__((used)) static void timer_call(struct script_callback *p_cb)
{
	struct python_obs_callback *cb = (struct python_obs_callback *)p_cb;

	if (p_cb->removed)
		return;

	lock_callback(cb);
	PyObject *py_ret = PyObject_CallObject(cb->func, NULL);
	py_error();
	Py_XDECREF(py_ret);
	unlock_callback();
}