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

__attribute__((used)) static double quadric(params *p, double x)
{
    if (x <  0.75) {
        return 0.75 - x * x;
    } else if (x <  1.5) {
        double t = x - 1.5;
        return 0.5 * t * t;
    }
    return 0.0;
}