#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* f; } ;
struct TYPE_5__ {int (* fromstr ) (char*,void*,char**,TYPE_2__*) ;} ;
typedef  TYPE_2__ PyArray_Descr ;

/* Variables and functions */
 scalar_t__ string_is_fully_read (char*,char const*) ; 
 int stub1 (char*,void*,char**,TYPE_2__*) ; 

__attribute__((used)) static int
fromstr_next_element(char **s, void *dptr, PyArray_Descr *dtype,
                     const char *end)
{
    char *e = *s;
    int r = dtype->f->fromstr(*s, dptr, &e, dtype);
    /*
     * fromstr always returns 0 for basic dtypes; s points to the end of the
     * parsed string. If s is not changed an error occurred or the end was
     * reached.
     */
    if (*s == e || r < 0) {
        /* Nothing read, could be end of string or an error (or both) */
        if (string_is_fully_read(*s, end)) {
            return -1;
        }
        return -2;
    }
    *s = e;
    if (end != NULL && *s > end) {
        /* Stop the iteration if we read far enough */
        return -1;
    }
    return 0;
}