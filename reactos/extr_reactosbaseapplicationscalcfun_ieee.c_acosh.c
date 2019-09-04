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
 double log (double) ; 
 double sqrt (double) ; 

double acosh(double x)
{
    // must be x>=1, if not return Nan (Not a Number)
    if(!(x>=1.0)) return sqrt(-1.0);
    
    // return only the positive result (as sqrt does).
    return log(x+sqrt(x*x-1.0));
}