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
typedef  int /*<<< orphan*/  params ;

/* Variables and functions */

__attribute__((used)) static double spline36(params *p, double x)
{
    if (x < 1.0) {
        return ((13.0/11.0 * x - 453.0/209.0) * x - 3.0/209.0) * x + 1.0;
    } else if (x < 2.0) {
        return ((-6.0/11.0 * (x-1) + 270.0/209.0) * (x-1) - 156.0/ 209.0) * (x-1);
    } else {
        return ((1.0/11.0 * (x-2) - 45.0/209.0) * (x-2) +  26.0/209.0) * (x-2);
    }
}