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
 int /*<<< orphan*/  change_decimal_from_locale_to_dot (char*) ; 
 int /*<<< orphan*/  ensure_decimal_point (char*,size_t) ; 
 int /*<<< orphan*/  ensure_minimum_exponent_length (char*,size_t) ; 

__attribute__((used)) static char*
fix_ascii_format(char* buf, size_t buflen, int decimal)
{
    /*
     * Get the current locale, and find the decimal point string.
     * Convert that string back to a dot.
     */
    change_decimal_from_locale_to_dot(buf);

    /*
     * If an exponent exists, ensure that the exponent is at least
     * MIN_EXPONENT_DIGITS digits, providing the buffer is large enough
     * for the extra zeros.  Also, if there are more than
     * MIN_EXPONENT_DIGITS, remove as many zeros as possible until we get
     * back to MIN_EXPONENT_DIGITS
     */
    ensure_minimum_exponent_length(buf, buflen);

    if (decimal != 0) {
        ensure_decimal_point(buf, buflen);
    }

    return buf;
}