#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int degr; } ;

/* Variables and functions */
 double CALC_PI ; 
#define  IDC_RADIO_DEG 130 
#define  IDC_RADIO_GRAD 129 
#define  IDC_RADIO_RAD 128 
 TYPE_1__ calc ; 

__attribute__((used)) static double validate_rad2angle(double a)
{
    switch (calc.degr) {
    case IDC_RADIO_DEG:
        a = a * (180.0/CALC_PI);
        break;
    case IDC_RADIO_RAD:
        break;
    case IDC_RADIO_GRAD:
        a = a * (200.0/CALC_PI);
        break;
    }
    return a;
}