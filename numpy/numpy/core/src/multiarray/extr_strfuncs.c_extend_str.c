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
typedef  int Py_ssize_t ;

/* Variables and functions */
 char* PyArray_realloc (char*,int) ; 

__attribute__((used)) static char *
extend_str(char **strp, Py_ssize_t n, Py_ssize_t *maxp)
{
    char *str = *strp;
    Py_ssize_t new_cap;

    if (n >= *maxp - 16) {
        new_cap = *maxp * 2;

        if (new_cap <= *maxp) {     /* overflow */
            return NULL;
        }
        str = PyArray_realloc(*strp, new_cap);
        if (str != NULL) {
            *strp = str;
            *maxp = new_cap;
        }
    }
    return str;
}