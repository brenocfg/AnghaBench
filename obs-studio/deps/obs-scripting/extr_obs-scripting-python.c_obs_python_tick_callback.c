#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ removed; } ;
struct python_obs_callback {int /*<<< orphan*/  func; TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PyObject_CallObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_BuildValue (char*,float) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_callback (struct python_obs_callback*) ; 
 int /*<<< orphan*/  obs_remove_tick_callback (void (*) (void*,float),struct python_obs_callback*) ; 
 int /*<<< orphan*/  py_error () ; 
 int /*<<< orphan*/  unlock_callback () ; 

__attribute__((used)) static void obs_python_tick_callback(void *priv, float seconds)
{
	struct python_obs_callback *cb = priv;

	if (cb->base.removed) {
		obs_remove_tick_callback(obs_python_tick_callback, cb);
		return;
	}

	lock_callback(cb);

	PyObject *args = Py_BuildValue("(f)", seconds);
	PyObject *py_ret = PyObject_CallObject(cb->func, args);
	py_error();
	Py_XDECREF(py_ret);
	Py_XDECREF(args);

	unlock_callback();
}