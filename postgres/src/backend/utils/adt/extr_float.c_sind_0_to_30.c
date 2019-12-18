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
 double RADIANS_PER_DEGREE ; 
 double sin (double) ; 
 double volatile sin_30 ; 

__attribute__((used)) static double
sind_0_to_30(double x)
{
	volatile float8 sin_x = sin(x * RADIANS_PER_DEGREE);

	return (sin_x / sin_30) / 2.0;
}