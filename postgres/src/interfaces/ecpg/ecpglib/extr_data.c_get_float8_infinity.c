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
 int HUGE_VAL ; 
 scalar_t__ INFINITY ; 

__attribute__((used)) static double
get_float8_infinity(void)
{
#ifdef INFINITY
	return (double) INFINITY;
#else
	return (double) (HUGE_VAL * HUGE_VAL);
#endif
}