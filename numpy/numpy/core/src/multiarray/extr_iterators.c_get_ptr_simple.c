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
typedef  size_t npy_intp ;
struct TYPE_3__ {size_t const* strides; int /*<<< orphan*/  ao; } ;
typedef  TYPE_1__ PyArrayIterObject ;

/* Variables and functions */
 char* PyArray_DATA (int /*<<< orphan*/ ) ; 
 size_t PyArray_NDIM (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char*
get_ptr_simple(PyArrayIterObject* iter, const npy_intp *coordinates)
{
    npy_intp i;
    char *ret;

    ret = PyArray_DATA(iter->ao);

    for(i = 0; i < PyArray_NDIM(iter->ao); ++i) {
            ret += coordinates[i] * iter->strides[i];
    }

    return ret;
}