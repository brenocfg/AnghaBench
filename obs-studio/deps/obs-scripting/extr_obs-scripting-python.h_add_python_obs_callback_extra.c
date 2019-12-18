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
struct python_obs_callback {int /*<<< orphan*/ * func; } ;
struct obs_python_script {int /*<<< orphan*/  first_callback; } ;
typedef  int /*<<< orphan*/  obs_script_t ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  Py_XINCREF (int /*<<< orphan*/ *) ; 
 struct python_obs_callback* add_script_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline struct python_obs_callback *
add_python_obs_callback_extra(struct obs_python_script *script, PyObject *func,
			      size_t extra_size)
{
	struct python_obs_callback *cb = add_script_callback(
		&script->first_callback, (obs_script_t *)script,
		sizeof(*cb) + extra_size);

	Py_XINCREF(func);
	cb->func = func;
	return cb;
}