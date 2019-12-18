#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 double INFINITY ; 
 double fabs (double) ; 
 double rint (double) ; 

__attribute__((used)) static double calc_best_speed(double vsync, double frame)
{
    double ratio = frame / vsync;
    double best_scale = -1;
    double best_dev = INFINITY;
    for (int factor = 1; factor <= 5; factor++) {
        double scale = ratio * factor / rint(ratio * factor);
        double dev = fabs(scale - 1);
        if (dev < best_dev) {
            best_scale = scale;
            best_dev = dev;
        }
    }
    return best_scale;
}