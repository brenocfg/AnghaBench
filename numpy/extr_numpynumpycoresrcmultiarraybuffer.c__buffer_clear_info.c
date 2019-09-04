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
typedef  int /*<<< orphan*/  _buffer_info_t ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyDict_DelItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyDict_GetItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyList_GET_ITEM (int /*<<< orphan*/ *,int) ; 
 int PyList_GET_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ PyLong_AsVoidPtr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyLong_FromVoidPtr (void*) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _buffer_info_cache ; 
 int /*<<< orphan*/  _buffer_info_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
_buffer_clear_info(PyObject *arr)
{
    PyObject *key, *item_list, *item;
    _buffer_info_t *info;
    int k;

    if (_buffer_info_cache == NULL) {
        return;
    }

    key = PyLong_FromVoidPtr((void*)arr);
    item_list = PyDict_GetItem(_buffer_info_cache, key);
    if (item_list != NULL) {
        for (k = 0; k < PyList_GET_SIZE(item_list); ++k) {
            item = PyList_GET_ITEM(item_list, k);
            info = (_buffer_info_t*)PyLong_AsVoidPtr(item);
            _buffer_info_free(info);
        }
        PyDict_DelItem(_buffer_info_cache, key);
    }

    Py_DECREF(key);
}