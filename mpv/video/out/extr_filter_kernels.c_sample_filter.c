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
struct TYPE_2__ {double radius; } ;
struct filter_kernel {int clamp; TYPE_1__ f; TYPE_1__ w; } ;

/* Variables and functions */
 double sample_window (TYPE_1__*,double) ; 

__attribute__((used)) static double sample_filter(struct filter_kernel *filter, double x)
{
    // The window is always stretched to the entire kernel
    double w = sample_window(&filter->w, x / filter->f.radius * filter->w.radius);
    double k = w * sample_window(&filter->f, x);
    return k < 0 ? (1 - filter->clamp) * k : k;
}