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
typedef  int /*<<< orphan*/  PyArrayIterObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyArray_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_iter_base_dealloc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
arrayiter_dealloc(PyArrayIterObject *it)
{
    /*
     * Note that it is possible to statically allocate a PyArrayIterObject,
     * which does not call this function.
     */
    array_iter_base_dealloc(it);
    PyArray_free(it);
}