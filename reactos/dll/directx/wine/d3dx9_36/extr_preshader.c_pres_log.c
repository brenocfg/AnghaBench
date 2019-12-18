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
 double fabs (double) ; 
 double log (int) ; 
 double log2 (double) ; 

__attribute__((used)) static double pres_log(double *args, int n)
{
    double v;

    v = fabs(args[0]);
    if (v == 0.0)
        return 0.0;
    else
#ifdef HAVE_LOG2
        return log2(v);
#else
        return log(v) / log(2);
#endif
}