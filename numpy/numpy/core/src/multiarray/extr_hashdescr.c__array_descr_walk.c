#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  subarray; int /*<<< orphan*/ * fields; int /*<<< orphan*/  names; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PyArray_Descr ;

/* Variables and functions */
 scalar_t__ PyDataType_HASSUBARRAY (TYPE_1__*) ; 
 int /*<<< orphan*/ * Py_None ; 
 int _array_descr_builtin (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int _array_descr_walk_fields (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int _array_descr_walk_subarray (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ _is_array_descr_builtin (TYPE_1__*) ; 

__attribute__((used)) static int _array_descr_walk(PyArray_Descr* descr, PyObject *l)
{
    int st;

    if (_is_array_descr_builtin(descr)) {
        return _array_descr_builtin(descr, l);
    }
    else {
        if(descr->fields != NULL && descr->fields != Py_None) {
            st = _array_descr_walk_fields(descr->names, descr->fields, l);
            if (st) {
                return -1;
            }
        }
        if(PyDataType_HASSUBARRAY(descr)) {
            st = _array_descr_walk_subarray(descr->subarray, l);
            if (st) {
                return -1;
            }
        }
    }

    return 0;
}