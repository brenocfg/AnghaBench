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
 int fabs (double const) ; 
 double const pow (double const,double const) ; 

__attribute__((used)) static double filter_power(const double x)
{
	const double a = 2.0f;
	if (fabs(x)>1) return 0.0f;
	return (1.0f - (double)fabs(pow(x,a)));
}