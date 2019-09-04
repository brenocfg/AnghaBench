#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  f; } ;
typedef  TYPE_1__ calc_number_t ;
struct TYPE_6__ {int /*<<< orphan*/  is_nan; } ;

/* Variables and functions */
 double CALC_2_PI ; 
 double CALC_3_PI_2 ; 
 double CALC_PI ; 
 double CALC_PI_2 ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_4__ calc ; 
 int /*<<< orphan*/  tan (double) ; 
 double validate_angle2rad (TYPE_1__*) ; 

void rpn_tan(calc_number_t *c)
{
    double angle = validate_angle2rad(c);

    if (angle == CALC_PI_2 || angle == CALC_3_PI_2)
        calc.is_nan = TRUE;
    else
    if (angle == CALC_PI || angle == CALC_2_PI)
        c->f = 0;
    else
        c->f = tan(angle);
}