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
struct python_obs_callback {int dummy; } ;
struct obs_python_script {int dummy; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyFunction_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 struct python_obs_callback* add_python_obs_callback (struct obs_python_script*,int /*<<< orphan*/ *) ; 
 struct obs_python_script* cur_python_script ; 
 int /*<<< orphan*/  modified_callback ; 
 int /*<<< orphan*/  obs_property_set_modified_callback2 (int,int /*<<< orphan*/ ,struct python_obs_callback*) ; 
 int obs_property_t ; 
 int p ; 
 int /*<<< orphan*/  parse_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  py_to_libobs (int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * python_none () ; 

__attribute__((used)) static PyObject *property_set_modified_callback(PyObject *self, PyObject *args)
{
	struct obs_python_script *script = cur_python_script;
	PyObject *py_p;
	PyObject *py_cb;
	obs_property_t *p;

	if (!parse_args(args, "OO", &py_p, &py_cb))
		return python_none();
	if (!py_to_libobs(obs_property_t, py_p, &p))
		return python_none();
	if (!py_cb || !PyFunction_Check(py_cb))
		return python_none();

	struct python_obs_callback *cb = add_python_obs_callback(script, py_cb);
	obs_property_set_modified_callback2(p, modified_callback, cb);

	UNUSED_PARAMETER(self);
	return python_none();
}