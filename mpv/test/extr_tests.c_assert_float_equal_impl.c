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
 int /*<<< orphan*/  abort () ; 
 double fabs (double) ; 
 int /*<<< orphan*/  printf (char*,char const*,int,double,double) ; 

void assert_float_equal_impl(const char *file, int line,
                              double a, double b, double tolerance)
{
    if (fabs(a - b) > tolerance) {
        printf("%s:%d: %f != %f\n", file, line, a, b);
        abort();
    }
}