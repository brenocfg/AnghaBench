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
 int /*<<< orphan*/ * PyCObject_FromVoidPtr (void*,void (*) (void*)) ; 

PyObject *
F2PyCapsule_FromVoidPtr(void *ptr, void (*dtor)(void *))
{
    return PyCObject_FromVoidPtr(ptr, dtor);
}