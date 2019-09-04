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
 double M_PI ; 
 int fabs (double) ; 
 double j1 (double) ; 

__attribute__((used)) static double jinc(params *p, double x)
{
    if (fabs(x) < 1e-8)
        return 1.0;
    x *= M_PI;
    return 2.0 * j1(x) / x;
}