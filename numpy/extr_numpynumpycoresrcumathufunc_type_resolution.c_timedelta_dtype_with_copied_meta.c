#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  meta; } ;
struct TYPE_6__ {scalar_t__ c_metadata; } ;
typedef  TYPE_1__ PyArray_Descr ;
typedef  int /*<<< orphan*/  PyArray_DatetimeMetaData ;
typedef  TYPE_2__ PyArray_DatetimeDTypeMetaData ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_TIMEDELTA ; 
 TYPE_1__* PyArray_DescrNewFromType (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyArray_Descr *
timedelta_dtype_with_copied_meta(PyArray_Descr *dtype)
{
    PyArray_Descr *ret;
    PyArray_DatetimeMetaData *dst, *src;
    PyArray_DatetimeDTypeMetaData *dst_dtmd, *src_dtmd;

    ret = PyArray_DescrNewFromType(NPY_TIMEDELTA);
    if (ret == NULL) {
        return NULL;
    }

    src_dtmd = ((PyArray_DatetimeDTypeMetaData *)dtype->c_metadata);
    dst_dtmd = ((PyArray_DatetimeDTypeMetaData *)ret->c_metadata);
    src = &(src_dtmd->meta);
    dst = &(dst_dtmd->meta);

    *dst = *src;

    return ret;
}