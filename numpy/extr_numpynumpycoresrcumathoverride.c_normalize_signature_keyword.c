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
 int /*<<< orphan*/  PyDict_DelItemString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * PyDict_GetItemString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PyDict_SetItemString (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 

__attribute__((used)) static int
normalize_signature_keyword(PyObject *normal_kwds)
{
    PyObject* obj = PyDict_GetItemString(normal_kwds, "sig");
    if (obj != NULL) {
        if (PyDict_GetItemString(normal_kwds, "signature")) {
            PyErr_SetString(PyExc_TypeError,
                            "cannot specify both 'sig' and 'signature'");
            return -1;
        }
        /*
         * No INCREF or DECREF needed: got a borrowed reference above,
         * and, unlike e.g. PyList_SetItem, PyDict_SetItem INCREF's it.
         */
        PyDict_SetItemString(normal_kwds, "signature", obj);
        PyDict_DelItemString(normal_kwds, "sig");
    }
    return 0;
}