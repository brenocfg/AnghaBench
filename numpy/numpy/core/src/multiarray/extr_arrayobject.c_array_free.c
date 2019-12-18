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
 int /*<<< orphan*/  PyObject_Free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
array_free(PyObject * v)
{
    /* avoid same deallocator as PyBaseObject, see gentype_free */
    PyObject_Free(v);
}