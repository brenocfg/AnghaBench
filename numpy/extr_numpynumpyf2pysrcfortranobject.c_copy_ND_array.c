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
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/  F2PY_REPORT_ON_ARRAY_COPY_FROMARR ; 
 int PyArray_CopyInto (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

extern
int copy_ND_array(const PyArrayObject *arr, PyArrayObject *out)
{
    F2PY_REPORT_ON_ARRAY_COPY_FROMARR;
    return PyArray_CopyInto(out, (PyArrayObject *)arr);
}