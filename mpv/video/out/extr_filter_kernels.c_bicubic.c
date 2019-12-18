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
 int POW3 (double) ; 

__attribute__((used)) static double bicubic(params *p, double x)
{
    return (1.0/6.0) * (      POW3(x + 2)
                        - 4 * POW3(x + 1)
                        + 6 * POW3(x)
                        - 4 * POW3(x - 1));
}