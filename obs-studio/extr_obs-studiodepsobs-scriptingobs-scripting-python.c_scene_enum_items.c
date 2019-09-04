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
 int /*<<< orphan*/ * PyList_New (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enum_items_proc ; 
 int /*<<< orphan*/  obs_scene_enum_items (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int obs_scene_t ; 
 int /*<<< orphan*/  parse_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  py_to_libobs (int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * python_none () ; 
 int scene ; 

__attribute__((used)) static PyObject *scene_enum_items(PyObject *self, PyObject *args)
{
	PyObject *py_scene;
	obs_scene_t *scene;

	UNUSED_PARAMETER(self);

	if (!parse_args(args, "O", &py_scene))
		return python_none();
	if (!py_to_libobs(obs_scene_t, py_scene, &scene))
		return python_none();

	PyObject *list = PyList_New(0);
	obs_scene_enum_items(scene, enum_items_proc, list);
	return list;
}