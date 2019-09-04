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
 scalar_t__ ERANGE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 double strtod (char const*,char**) ; 
 scalar_t__ xisspace (char) ; 

bool safe_strtod(const char *str, double *out) {
    assert(out != NULL);
    errno = 0;
    *out = 0;
    char *endptr;
    double d = strtod(str, &endptr);
    if ((errno == ERANGE) || (str == endptr)) {
        return false;
    }

    if (xisspace(*endptr) || (*endptr == '\0' && endptr != str)) {
        *out = d;
        return true;
    }
    return false;
}