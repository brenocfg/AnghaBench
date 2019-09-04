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
struct TYPE_2__ {double d; int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ double_s_t ;

/* Variables and functions */

double copysign(double x, double y) {
    double_s_t dx={.d = x};
    double_s_t dy={.d = y};

    // copy sign bit;
    dx.s = dy.s;

    return dx.d;
}