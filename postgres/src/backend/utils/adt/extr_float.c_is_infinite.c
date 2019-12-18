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
 int isinf (double) ; 

int
is_infinite(double val)
{
	int			inf = isinf(val);

	if (inf == 0)
		return 0;
	else if (val > 0)
		return 1;
	else
		return -1;
}