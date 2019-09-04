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

__attribute__((used)) static double filter_quadratic(const double x1)
{
	const double x = x1 < 0.0 ? -x1 : x1;

	if (x <= 0.5) return (- 2.0 * x * x + 1);
	if (x <= 1.5) return (x * x - 2.5* x + 1.5);
	return 0.0;
}