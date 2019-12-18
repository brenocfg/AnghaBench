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
 double exp (double) ; 

__attribute__((used)) static double gaussian(params *p, double x)
{
    return exp(-2.0 * x * x / p->params[0]);
}