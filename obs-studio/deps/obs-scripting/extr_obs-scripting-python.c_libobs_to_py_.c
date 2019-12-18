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
typedef  int /*<<< orphan*/  swig_type_info ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * Py_None ; 
 int /*<<< orphan*/ * SWIG_NewPointerObj (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * SWIG_TypeQuery (char const*) ; 
 int /*<<< orphan*/  warn (char*,char const*,int,char const*,char*,char const*) ; 

bool libobs_to_py_(const char *type, void *libobs_in, bool ownership,
		   PyObject **py_out, const char *id, const char *func,
		   int line)
{
	swig_type_info *info = SWIG_TypeQuery(type);
	if (info == NULL) {
		warn("%s:%d: SWIG could not find type: %s%s%s", func, line,
		     id ? id : "", id ? "::" : "", type);
		return false;
	}

	*py_out = SWIG_NewPointerObj(libobs_in, info, (int)ownership);
	if (*py_out == Py_None) {
		warn("%s:%d: SWIG failed to convert obs object to python "
		     "object: %s%s%s",
		     func, line, id ? id : "", id ? "::" : "", type);
		return false;
	}

	return true;
}