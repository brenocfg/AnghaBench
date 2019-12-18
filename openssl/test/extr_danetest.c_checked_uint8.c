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
typedef  long uint8_t ;
typedef  int ossl_ssize_t ;

/* Variables and functions */
 int ERANGE ; 
 long LONG_MAX ; 
 long LONG_MIN ; 
 int /*<<< orphan*/  _UC (char const) ; 
 scalar_t__ isspace (int /*<<< orphan*/ ) ; 
 int restore_errno () ; 
 int /*<<< orphan*/  save_errno () ; 
 long strtol (char const*,char**,int) ; 

__attribute__((used)) static ossl_ssize_t checked_uint8(const char *in, void *out)
{
    uint8_t *result = (uint8_t *)out;
    const char *cp = in;
    char *endp;
    long v;
    int e;

    save_errno();
    v = strtol(cp, &endp, 10);
    e = restore_errno();

    if (((v == LONG_MIN || v == LONG_MAX) && e == ERANGE) ||
        endp == cp || !isspace(_UC(*endp)) ||
        v != (*(uint8_t *)result = (uint8_t) v)) {
        return -1;
    }
    for (cp = endp; isspace(_UC(*cp)); ++cp)
        continue;
    return cp - in;
}