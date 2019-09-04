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
 int MIN_EXPONENT_DIGITS ; 
 int /*<<< orphan*/  Py_CHARMASK (char) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ isdigit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 char* strpbrk (char*,char*) ; 

__attribute__((used)) static void
ensure_minimum_exponent_length(char* buffer, size_t buf_size)
{
    char *p = strpbrk(buffer, "eE");
    if (p && (*(p + 1) == '-' || *(p + 1) == '+')) {
        char *start = p + 2;
        int exponent_digit_cnt = 0;
        int leading_zero_cnt = 0;
        int in_leading_zeros = 1;
        int significant_digit_cnt;

        /* Skip over the exponent and the sign. */
        p += 2;

        /* Find the end of the exponent, keeping track of leading zeros. */
        while (*p && isdigit(Py_CHARMASK(*p))) {
            if (in_leading_zeros && *p == '0') {
                ++leading_zero_cnt;
            }
            if (*p != '0') {
                in_leading_zeros = 0;
            }
            ++p;
            ++exponent_digit_cnt;
        }

        significant_digit_cnt = exponent_digit_cnt - leading_zero_cnt;
        if (exponent_digit_cnt == MIN_EXPONENT_DIGITS) {
            /*
             * If there are 2 exactly digits, we're done,
             * regardless of what they contain
             */
        }
        else if (exponent_digit_cnt > MIN_EXPONENT_DIGITS) {
            int extra_zeros_cnt;

            /*
             * There are more than 2 digits in the exponent.  See
             * if we can delete some of the leading zeros
             */
            if (significant_digit_cnt < MIN_EXPONENT_DIGITS) {
                significant_digit_cnt = MIN_EXPONENT_DIGITS;
            }
            extra_zeros_cnt = exponent_digit_cnt - significant_digit_cnt;

            /*
             * Delete extra_zeros_cnt worth of characters from the
             * front of the exponent
             */
            assert(extra_zeros_cnt >= 0);

            /*
             * Add one to significant_digit_cnt to copy the
             * trailing 0 byte, thus setting the length
             */
            memmove(start, start + extra_zeros_cnt, significant_digit_cnt + 1);
        }
        else {
            /*
             * If there are fewer than 2 digits, add zeros
             * until there are 2, if there's enough room
             */
            int zeros = MIN_EXPONENT_DIGITS - exponent_digit_cnt;
            if (start + zeros + exponent_digit_cnt + 1 < buffer + buf_size) {
                memmove(start + zeros, start, exponent_digit_cnt + 1);
                memset(start, '0', zeros);
            }
        }
    }
}