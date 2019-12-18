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
 int /*<<< orphan*/  modf (double,double*) ; 
 double to_digit (char) ; 

__attribute__((used)) static char *
c_round(double fract, int *exp, char *start, char *end, char ch, char *signp)
{
    double tmp;

    if (fract)
        (void)modf(fract * 10, &tmp);
    else
        tmp = to_digit(ch);
    if (tmp > 4)
        for (;; --end) {
            if (*end == '.')
                --end;
            if (++*end <= '9')
                break;
            *end = '0';
            if (end == start) {
                if (exp) {  /* e/E; increment exponent */
                    *end = '1';
                    ++*exp;
                }
                else {      /* f; add extra digit */
                *--end = '1';
                --start;
                }
                break;
            }
        }
    /* ``"%.3f", (double)-0.0004'' gives you a negative 0. */
    else if (*signp == '-')
        for (;; --end) {
            if (*end == '.')
                --end;
            if (*end != '0')
                break;
            if (end == start)
                *signp = 0;
        }
    return (start);
}