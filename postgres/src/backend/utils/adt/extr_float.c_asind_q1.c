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
typedef  double float8 ;

/* Variables and functions */
 double acos (double) ; 
 double volatile acos_0_5 ; 
 double asin (double) ; 
 double volatile asin_0_5 ; 

__attribute__((used)) static double
asind_q1(double x)
{
	/*
	 * Stitch together inverse sine and cosine functions for the ranges [0,
	 * 0.5] and (0.5, 1].  Each expression below is guaranteed to return
	 * exactly 30 for x=0.5, so the result is a continuous monotonic function
	 * over the full range.
	 */
	if (x <= 0.5)
	{
		volatile float8 asin_x = asin(x);

		return (asin_x / asin_0_5) * 30.0;
	}
	else
	{
		volatile float8 acos_x = acos(x);

		return 90.0 - (acos_x / acos_0_5) * 60.0;
	}
}