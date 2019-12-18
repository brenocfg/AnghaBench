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
struct vo_internal {int num_vsync_samples; double* vsync_samples; } ;
struct vo {struct vo_internal* in; } ;
typedef  double int64_t ;

/* Variables and functions */
 double sqrt (double) ; 

__attribute__((used)) static double vsync_stddef(struct vo *vo, int64_t ref_vsync)
{
    struct vo_internal *in = vo->in;
    double jitter = 0;
    for (int n = 0; n < in->num_vsync_samples; n++) {
        double diff = in->vsync_samples[n] - ref_vsync;
        jitter += diff * diff;
    }
    return sqrt(jitter / in->num_vsync_samples);
}