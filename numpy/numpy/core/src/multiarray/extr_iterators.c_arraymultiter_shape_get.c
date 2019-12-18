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
struct TYPE_3__ {int /*<<< orphan*/  dimensions; int /*<<< orphan*/  nd; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PyArrayMultiIterObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PyArray_IntTupleFromIntp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
arraymultiter_shape_get(PyArrayMultiIterObject *self)
{
    return PyArray_IntTupleFromIntp(self->nd, self->dimensions);
}