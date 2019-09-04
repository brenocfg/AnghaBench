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
struct TYPE_4__ {int /*<<< orphan*/ * fields; } ;
typedef  TYPE_1__ PyArray_Descr ;

/* Variables and functions */
 scalar_t__ PyDataType_HASSUBARRAY (TYPE_1__*) ; 
 int /*<<< orphan*/ * Py_None ; 

__attribute__((used)) static int _is_array_descr_builtin(PyArray_Descr* descr)
{
    if (descr->fields != NULL && descr->fields != Py_None) {
        return 0;
    }
    if (PyDataType_HASSUBARRAY(descr)) {
        return 0;
    }
    return 1;
}