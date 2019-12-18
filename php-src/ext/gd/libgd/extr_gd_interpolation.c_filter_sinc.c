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
 double M_PI ; 
 double sin (double) ; 

__attribute__((used)) static double filter_sinc(const double x)
{
	/* X-scaled Sinc(x) function. */
	if (x == 0.0) return(1.0);
	return (sin(M_PI * (double) x) / (M_PI * (double) x));
}