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
typedef  int /*<<< orphan*/  numeric ;

/* Variables and functions */
 scalar_t__ numericvar_to_double (int /*<<< orphan*/ *,double*) ; 

int
PGTYPESnumeric_to_double(numeric *nv, double *dp)
{
	double		tmp;

	if (numericvar_to_double(nv, &tmp) != 0)
		return -1;
	*dp = tmp;
	return 0;
}