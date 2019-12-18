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
struct TYPE_4__ {char* length; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ strbuffer_t ;

/* Variables and functions */
 scalar_t__ ERANGE ; 
 double HUGE_VAL ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 double strtod (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  to_locale (TYPE_1__*) ; 

int jsonp_strtod(strbuffer_t *strbuffer, double *out)
{
    double value;
    char *end;

#if JSON_HAVE_LOCALECONV
    to_locale(strbuffer);
#endif

    errno = 0;
    value = strtod(strbuffer->value, &end);
    assert(end == strbuffer->value + strbuffer->length);

    if((value == HUGE_VAL || value == -HUGE_VAL) && errno == ERANGE) {
        /* Overflow */
        return -1;
    }

    *out = value;
    return 0;
}