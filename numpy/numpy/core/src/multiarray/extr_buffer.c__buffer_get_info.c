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
 int /*<<< orphan*/ * PyDict_GetItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyDict_New () ; 
 scalar_t__ PyDict_SetItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyList_Append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ PyList_GET_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyList_GetItem (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * PyList_New (int /*<<< orphan*/ ) ; 
 scalar_t__ PyLong_AsVoidPtr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyLong_FromVoidPtr (void*) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _buffer_info_cache ; 
 scalar_t__ _buffer_info_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _buffer_info_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _buffer_info_new (int /*<<< orphan*/ *) ; 

__attribute__((used)) static _buffer_info_t*
_buffer_get_info(PyObject *obj)
{
    PyObject *key = NULL, *item_list = NULL, *item = NULL;
    _buffer_info_t *info = NULL, *old_info = NULL;

    if (_buffer_info_cache == NULL) {
        _buffer_info_cache = PyDict_New();
        if (_buffer_info_cache == NULL) {
            return NULL;
        }
    }

    /* Compute information */
    info = _buffer_info_new(obj);
    if (info == NULL) {
        return NULL;
    }

    /* Check if it is identical with an old one; reuse old one, if yes */
    key = PyLong_FromVoidPtr((void*)obj);
    if (key == NULL) {
        goto fail;
    }
    item_list = PyDict_GetItem(_buffer_info_cache, key);

    if (item_list != NULL) {
        Py_INCREF(item_list);
        if (PyList_GET_SIZE(item_list) > 0) {
            item = PyList_GetItem(item_list, PyList_GET_SIZE(item_list) - 1);
            old_info = (_buffer_info_t*)PyLong_AsVoidPtr(item);

            if (_buffer_info_cmp(info, old_info) == 0) {
                _buffer_info_free(info);
                info = old_info;
            }
        }
    }
    else {
        item_list = PyList_New(0);
        if (item_list == NULL) {
            goto fail;
        }
        if (PyDict_SetItem(_buffer_info_cache, key, item_list) != 0) {
            goto fail;
        }
    }

    if (info != old_info) {
        /* Needs insertion */
        item = PyLong_FromVoidPtr((void*)info);
        if (item == NULL) {
            goto fail;
        }
        PyList_Append(item_list, item);
        Py_DECREF(item);
    }

    Py_DECREF(item_list);
    Py_DECREF(key);
    return info;

fail:
    if (info != NULL && info != old_info) {
        _buffer_info_free(info);
    }
    Py_XDECREF(item_list);
    Py_XDECREF(key);
    return NULL;
}