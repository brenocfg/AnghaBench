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
typedef  int uint64_t ;

/* Variables and functions */

__attribute__((used)) static int atou64(const char *nptr, uint64_t *result)
{
    uint64_t value = 0;

    while (*nptr) {
        unsigned int digit;
        uint64_t new_value;

        if ((*nptr < '0') || (*nptr > '9')) {
            return 0;
        }
        digit = (unsigned int)(*nptr - '0');
        new_value = (value * 10) + digit;
        if ((new_value < digit) || ((new_value - digit) / 10 != value)) {
            /* Overflow */
            return 0;
        }
        value = new_value;
        nptr++;
    }
    *result = value;
    return 1;
}