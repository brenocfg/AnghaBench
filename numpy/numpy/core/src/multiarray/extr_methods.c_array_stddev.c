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
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_FORWARD_NDARRAY_METHOD (char*) ; 

__attribute__((used)) static PyObject *
array_stddev(PyArrayObject *self, PyObject *args, PyObject *kwds)
{
    NPY_FORWARD_NDARRAY_METHOD("_std");
}