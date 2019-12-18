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
 int /*<<< orphan*/  PyArray_IsIntegerScalar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyTuple_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyTuple_GET_ITEM (int /*<<< orphan*/ *,int) ; 
 int PyTuple_GET_SIZE (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
_is_tuple_of_integers(PyObject *obj)
{
    int i;

    if (!PyTuple_Check(obj)) {
        return 0;
    }
    for (i = 0; i < PyTuple_GET_SIZE(obj); i++) {
        if (!PyArray_IsIntegerScalar(PyTuple_GET_ITEM(obj, i))) {
            return 0;
        }
    }
    return 1;
}