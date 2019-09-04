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
struct TYPE_3__ {double radius; } ;
typedef  TYPE_1__ params ;

/* Variables and functions */
 scalar_t__ fabs (double) ; 
 double fmax (double,scalar_t__) ; 

__attribute__((used)) static double triangle(params *p, double x)
{
    return fmax(0.0, 1.0 - fabs(x / p->radius));
}