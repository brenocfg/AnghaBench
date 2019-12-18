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
typedef  enum tep_print_arg_type { ____Placeholder_tep_print_arg_type } tep_print_arg_type ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PyTuple_New (int) ; 
 int /*<<< orphan*/  PyTuple_SetItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_FatalError (char*) ; 
 int TEP_PRINT_SYMBOL ; 
 int /*<<< orphan*/  _PyLong_FromLong (unsigned long long) ; 
 int /*<<< orphan*/  _PyUnicode_FromString (char const*) ; 
 unsigned long long eval_flag (char const*) ; 
 int /*<<< orphan*/  try_call_object (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void define_value(enum tep_print_arg_type field_type,
			 const char *ev_name,
			 const char *field_name,
			 const char *field_value,
			 const char *field_str)
{
	const char *handler_name = "define_flag_value";
	PyObject *t;
	unsigned long long value;
	unsigned n = 0;

	if (field_type == TEP_PRINT_SYMBOL)
		handler_name = "define_symbolic_value";

	t = PyTuple_New(4);
	if (!t)
		Py_FatalError("couldn't create Python tuple");

	value = eval_flag(field_value);

	PyTuple_SetItem(t, n++, _PyUnicode_FromString(ev_name));
	PyTuple_SetItem(t, n++, _PyUnicode_FromString(field_name));
	PyTuple_SetItem(t, n++, _PyLong_FromLong(value));
	PyTuple_SetItem(t, n++, _PyUnicode_FromString(field_str));

	try_call_object(handler_name, t);

	Py_DECREF(t);
}