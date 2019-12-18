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
 double const M_PI ; 
 double cos (double const) ; 

__attribute__((used)) static double filter_hanning(const double x)
{
	/* A Cosine windowing function */
	return(0.5 + 0.5 * cos(M_PI * x));
}