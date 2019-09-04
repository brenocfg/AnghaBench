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
struct TYPE_3__ {int as; int ps; int us; scalar_t__ sec; scalar_t__ min; scalar_t__ hour; int day; int month; } ;
typedef  TYPE_1__ npy_datetimestruct ;
typedef  int /*<<< orphan*/  NPY_DATETIMEUNIT ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_FR_D ; 
 int /*<<< orphan*/  NPY_FR_M ; 
 int /*<<< orphan*/  NPY_FR_Y ; 
 int /*<<< orphan*/  NPY_FR_as ; 
 int /*<<< orphan*/  NPY_FR_fs ; 
 int /*<<< orphan*/  NPY_FR_h ; 
 int /*<<< orphan*/  NPY_FR_m ; 
 int /*<<< orphan*/  NPY_FR_ms ; 
 int /*<<< orphan*/  NPY_FR_ns ; 
 int /*<<< orphan*/  NPY_FR_ps ; 
 int /*<<< orphan*/  NPY_FR_s ; 
 int /*<<< orphan*/  NPY_FR_us ; 

__attribute__((used)) static NPY_DATETIMEUNIT
lossless_unit_from_datetimestruct(npy_datetimestruct *dts)
{
    if (dts->as % 1000 != 0) {
        return NPY_FR_as;
    }
    else if (dts->as != 0) {
        return NPY_FR_fs;
    }
    else if (dts->ps % 1000 != 0) {
        return NPY_FR_ps;
    }
    else if (dts->ps != 0) {
        return NPY_FR_ns;
    }
    else if (dts->us % 1000 != 0) {
        return NPY_FR_us;
    }
    else if (dts->us != 0) {
        return NPY_FR_ms;
    }
    else if (dts->sec != 0) {
        return NPY_FR_s;
    }
    else if (dts->min != 0) {
        return NPY_FR_m;
    }
    else if (dts->hour != 0) {
        return NPY_FR_h;
    }
    else if (dts->day != 1) {
        return NPY_FR_D;
    }
    else if (dts->month != 1) {
        return NPY_FR_M;
    }
    else {
        return NPY_FR_Y;
    }
}