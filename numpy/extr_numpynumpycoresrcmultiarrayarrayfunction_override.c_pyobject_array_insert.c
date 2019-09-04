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

__attribute__((used)) static void
pyobject_array_insert(PyObject **array, int length, int index, PyObject *item)
{
    int j;

    for (j = length; j > index; j--) {
        array[j] = array[j - 1];
    }
    array[index] = item;
}