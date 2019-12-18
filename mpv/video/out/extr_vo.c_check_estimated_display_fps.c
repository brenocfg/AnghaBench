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
struct vo_internal {int num_total_vsync_samples; int estimated_vsync_interval; int num_vsync_samples; int* vsync_samples; int nominal_vsync_interval; int vsync_interval; } ;
struct vo {struct vo_internal* in; } ;
typedef  int int64_t ;

/* Variables and functions */
 int MAX_VSYNC_SAMPLES ; 
 int /*<<< orphan*/  MP_VERBOSE (struct vo*,char*,int) ; 
 int fabs (int) ; 
 double vsync_stddef (struct vo*,int) ; 

__attribute__((used)) static void check_estimated_display_fps(struct vo *vo)
{
    struct vo_internal *in = vo->in;

    bool use_estimated = false;
    if (in->num_total_vsync_samples >= MAX_VSYNC_SAMPLES / 2 &&
        in->estimated_vsync_interval <= 1e6 / 20.0 &&
        in->estimated_vsync_interval >= 1e6 / 99.0)
    {
        for (int n = 0; n < in->num_vsync_samples; n++) {
            if (fabs(in->vsync_samples[n] - in->estimated_vsync_interval)
                >= in->estimated_vsync_interval / 4)
                goto done;
        }
        double mjitter = vsync_stddef(vo, in->estimated_vsync_interval);
        double njitter = vsync_stddef(vo, in->nominal_vsync_interval);
        if (mjitter * 1.01 < njitter)
            use_estimated = true;
        done: ;
    }
    if (use_estimated == (in->vsync_interval == in->nominal_vsync_interval)) {
        if (use_estimated) {
            MP_VERBOSE(vo, "adjusting display FPS to a value closer to %.3f Hz\n",
                       1e6 / in->estimated_vsync_interval);
        } else {
            MP_VERBOSE(vo, "switching back to assuming display fps = %.3f Hz\n",
                       1e6 / in->nominal_vsync_interval);
        }
    }
    in->vsync_interval = use_estimated ? (int64_t)in->estimated_vsync_interval
                                       : in->nominal_vsync_interval;
}