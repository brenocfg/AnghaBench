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
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PyUnicode_FromString (char*) ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfree (char*) ; 
 char* obs_frontend_get_current_scene_collection () ; 

__attribute__((used)) static PyObject *get_current_scene_collection(PyObject *self, PyObject *args)
{
	char *name = obs_frontend_get_current_scene_collection();
	PyObject *ret = PyUnicode_FromString(name);
	bfree(name);

	UNUSED_PARAMETER(self);
	UNUSED_PARAMETER(args);
	return ret;
}