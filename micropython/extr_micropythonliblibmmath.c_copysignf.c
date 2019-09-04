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
struct TYPE_2__ {float f; int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ float_s_t ;

/* Variables and functions */

float copysignf(float x, float y) {
    float_s_t fx={.f = x};
    float_s_t fy={.f = y};

    // copy sign bit;
    fx.s = fy.s;

    return fx.f;
}