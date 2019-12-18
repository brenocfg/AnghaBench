#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* name; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyDict_SetItemString (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ PyErr_Occurred () ; 
 int /*<<< orphan*/ * PyFortranObject_New (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyFortranObject_NewAsAttr (TYPE_1__*) ; 
 int /*<<< orphan*/ * PyModule_GetDict (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyString_FromString (char*) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_FatalError (char*) ; 
 int /*<<< orphan*/ * Py_InitModule (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2py_foodata_def ; 
 int /*<<< orphan*/  f2py_init_foodata ; 
 int /*<<< orphan*/  f2py_init_mod ; 
 int /*<<< orphan*/  f2py_mod_def ; 
 TYPE_1__* f2py_routines_def ; 
 int /*<<< orphan*/  foo_module_methods ; 
 int /*<<< orphan*/  import_array () ; 

void initfoo() {
    int i;
    PyObject *m, *d, *s, *tmp;
    import_array();

    m = Py_InitModule("foo", foo_module_methods);

    d = PyModule_GetDict(m);
    s = PyString_FromString("This module 'foo' demonstrates the usage of fortranobject.");
    PyDict_SetItemString(d, "__doc__", s);

    /* Fortran objects: */
    tmp = PyFortranObject_New(f2py_mod_def,f2py_init_mod);
    PyDict_SetItemString(d, "mod", tmp);
    Py_DECREF(tmp);
    tmp = PyFortranObject_New(f2py_foodata_def,f2py_init_foodata);
    PyDict_SetItemString(d, "foodata", tmp);
    Py_DECREF(tmp);
    for(i=0;f2py_routines_def[i].name!=NULL;i++) {
        tmp = PyFortranObject_NewAsAttr(&f2py_routines_def[i]);
        PyDict_SetItemString(d, f2py_routines_def[i].name, tmp);
        Py_DECREF(tmp);
    }

    Py_DECREF(s);

    if (PyErr_Occurred())
        Py_FatalError("can't initialize module foo");
}