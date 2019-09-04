#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int f; } ;
typedef  TYPE_1__ calc_number_t ;

/* Variables and functions */
 double CALC_2_PI ; 
 double CALC_3_PI_2 ; 
 double CALC_PI ; 
 int sin (double) ; 
 double validate_angle2rad (TYPE_1__*) ; 

void rpn_sin(calc_number_t *c)
{
    double angle = validate_angle2rad(c);

    if (angle == 0 || angle == CALC_PI)
        c->f = 0;
    else
    if (angle == CALC_3_PI_2)
        c->f = -1;
    else
    if (angle == CALC_2_PI)
        c->f = 1;
    else
        c->f = sin(angle);
}