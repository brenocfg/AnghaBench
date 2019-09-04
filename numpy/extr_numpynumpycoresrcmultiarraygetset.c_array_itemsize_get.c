#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ elsize; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 TYPE_1__* PyArray_DESCR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyInt_FromLong (long) ; 

__attribute__((used)) static PyObject *
array_itemsize_get(PyArrayObject *self)
{
    return PyInt_FromLong((long) PyArray_DESCR(self)->elsize);
}