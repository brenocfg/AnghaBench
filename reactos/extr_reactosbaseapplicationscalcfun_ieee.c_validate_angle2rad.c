#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {double f; } ;
typedef  TYPE_1__ calc_number_t ;
struct TYPE_5__ {int degr; } ;

/* Variables and functions */
 double CALC_PI ; 
#define  IDC_RADIO_DEG 130 
#define  IDC_RADIO_GRAD 129 
#define  IDC_RADIO_RAD 128 
 TYPE_3__ calc ; 

__attribute__((used)) static double validate_angle2rad(calc_number_t *c)
{
    switch (calc.degr) {
    case IDC_RADIO_DEG:
        c->f = c->f * (CALC_PI/180.0);
        break;
    case IDC_RADIO_RAD:
        break;
    case IDC_RADIO_GRAD:
        c->f = c->f * (CALC_PI/200.0);
        break;
    }
    return c->f;
}