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
typedef  int npy_hash_t ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArray_Descr ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_SystemError ; 
 int /*<<< orphan*/ * PyList_AsTuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyList_New (int /*<<< orphan*/ ) ; 
 int PyObject_Hash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int _array_descr_walk (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _PyArray_DescrHashImp(PyArray_Descr *descr, npy_hash_t *hash)
{
    PyObject *l, *tl;
    int st;

    l = PyList_New(0);
    if (l == NULL) {
        return -1;
    }

    st = _array_descr_walk(descr, l);
    if (st) {
        Py_DECREF(l);
        return -1;
    }

    /*
     * Convert the list to tuple and compute the tuple hash using python
     * builtin function
     */
    tl = PyList_AsTuple(l);
    Py_DECREF(l);
    if (tl == NULL)
        return -1;

    *hash = PyObject_Hash(tl);
    Py_DECREF(tl);
    if (*hash == -1) {
        /* XXX: does PyObject_Hash set an exception on failure ? */
#if 0
        PyErr_SetString(PyExc_SystemError,
                "(Hash) Error while hashing final tuple");
#endif
        return -1;
    }

    return 0;
}