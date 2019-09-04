#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {double* params; } ;
typedef  TYPE_1__ params ;

/* Variables and functions */
 double M_PI ; 
 double cos (int) ; 

__attribute__((used)) static double blackman(params *p, double x)
{
    double a = p->params[0];
    double a0 = (1-a)/2.0, a1 = 1/2.0, a2 = a/2.0;
    double pix = M_PI * x;
    return a0 + a1*cos(pix) + a2*cos(2 * pix);
}