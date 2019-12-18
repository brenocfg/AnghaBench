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

/* Variables and functions */
 int /*<<< orphan*/  NPY_ALLOW_C_API ; 
 int /*<<< orphan*/  NPY_ALLOW_C_API_DEF ; 
 int /*<<< orphan*/  NPY_DISABLE_C_API ; 
 int /*<<< orphan*/  PyErr_Clear () ; 
 scalar_t__ PyErr_Occurred () ; 
 double PyOS_string_to_double (char const*,char**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static double
NumPyOS_ascii_strtod_plain(const char *s, char** endptr)
{
    double result;
    NPY_ALLOW_C_API_DEF;
    NPY_ALLOW_C_API;
    result = PyOS_string_to_double(s, endptr, NULL);
    if (PyErr_Occurred()) {
        if (endptr) {
            *endptr = (char*)s;
        }
        PyErr_Clear();
    }
    NPY_DISABLE_C_API;
    return result;
}