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
struct TYPE_2__ {int /*<<< orphan*/  extra; int /*<<< orphan*/  on_remove; } ;
struct python_obs_callback {TYPE_1__ base; } ;
struct obs_python_script {int dummy; } ;
typedef  scalar_t__ obs_hotkey_id ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 scalar_t__ OBS_INVALID_HOTKEY_ID ; 
 int /*<<< orphan*/  PyFunction_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyLong_FromUnsignedLongLong (scalar_t__) ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 struct python_obs_callback* add_python_obs_callback (struct obs_python_script*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  calldata_set_int (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 struct obs_python_script* cur_python_script ; 
 int /*<<< orphan*/  hotkey_callback ; 
 scalar_t__ obs_hotkey_register_frontend (char const*,char const*,int /*<<< orphan*/ ,struct python_obs_callback*) ; 
 int /*<<< orphan*/  on_remove_hotkey ; 
 int /*<<< orphan*/  parse_args (int /*<<< orphan*/ *,char*,char const**,char const**,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * py_invalid_hotkey_id () ; 
 int /*<<< orphan*/  remove_python_obs_callback (struct python_obs_callback*) ; 

__attribute__((used)) static PyObject *hotkey_register_frontend(PyObject *self, PyObject *args)
{
	struct obs_python_script *script = cur_python_script;
	const char *name;
	const char *desc;
	obs_hotkey_id id;
	PyObject *py_cb;

	if (!parse_args(args, "ssO", &name, &desc, &py_cb))
		return py_invalid_hotkey_id();
	if (!py_cb || !PyFunction_Check(py_cb))
		return py_invalid_hotkey_id();

	struct python_obs_callback *cb = add_python_obs_callback(script, py_cb);
	cb->base.on_remove = on_remove_hotkey;
	id = obs_hotkey_register_frontend(name, desc, hotkey_callback, cb);
	calldata_set_int(&cb->base.extra, "id", id);

	if (id == OBS_INVALID_HOTKEY_ID)
		remove_python_obs_callback(cb);

	UNUSED_PARAMETER(self);
	return PyLong_FromUnsignedLongLong(id);
}