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

__attribute__((used)) static double
power_of_ten(int n)
{
    static const double p10[] = {1e0, 1e1, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7, 1e8};
    double ret;
    if (n < 9) {
        ret = p10[n];
    }
    else {
        ret = 1e9;
        while (n-- > 9) {
            ret *= 10.;
        }
    }
    return ret;
}