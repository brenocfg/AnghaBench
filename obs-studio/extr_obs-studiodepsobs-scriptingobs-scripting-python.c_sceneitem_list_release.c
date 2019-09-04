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
typedef  scalar_t__ Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PyList_GetItem (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ PyList_Size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int item ; 
 int /*<<< orphan*/  obs_sceneitem_release (int) ; 
 int obs_sceneitem_t ; 
 int /*<<< orphan*/  parse_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 scalar_t__ py_to_libobs (int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * python_none () ; 

__attribute__((used)) static PyObject *sceneitem_list_release(PyObject *self, PyObject *args)
{
	PyObject *list;
	if (!parse_args(args, "O", &list))
		return python_none();

	Py_ssize_t count = PyList_Size(list);
	for (Py_ssize_t i = 0; i < count; i++) {
		PyObject *py_item = PyList_GetItem(list, i);
		obs_sceneitem_t *item;

		if (py_to_libobs(obs_sceneitem_t, py_item, &item)) {
			obs_sceneitem_release(item);
		}
	}

	UNUSED_PARAMETER(self);
	return python_none();
}