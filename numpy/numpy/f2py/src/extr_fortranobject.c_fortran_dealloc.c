#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dict; } ;
typedef  TYPE_1__ PyFortranObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyObject_Del (TYPE_1__*) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fortran_dealloc(PyFortranObject *fp) {
    Py_XDECREF(fp->dict);
    PyObject_Del(fp);
}