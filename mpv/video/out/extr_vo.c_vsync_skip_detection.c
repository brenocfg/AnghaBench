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
struct vo_internal {int prev_vsync; int base_vsync; int drop_point; int* vsync_samples; int vsync_interval; int num_vsync_samples; int delayed_count; } ;
struct vo {struct vo_internal* in; } ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_STATS (struct vo*,char*) ; 
 int llabs (int) ; 

__attribute__((used)) static void vsync_skip_detection(struct vo *vo)
{
    struct vo_internal *in = vo->in;

    int window = 4;
    int64_t t_r = in->prev_vsync, t_e = in->base_vsync, diff = 0, desync_early = 0;
    for (int n = 0; n < in->drop_point; n++) {
        diff += t_r - t_e;
        t_r -= in->vsync_samples[n];
        t_e -= in->vsync_interval;
        if (n == window + 1)
            desync_early = diff / window;
    }
    int64_t desync = diff / in->num_vsync_samples;
    if (in->drop_point > window * 2 &&
        llabs(desync - desync_early) >= in->vsync_interval * 3 / 4)
    {
        // Assume a drop. An underflow can technically speaking not be a drop
        // (it's up to the driver what this is supposed to mean), but no reason
        // to treat it differently.
        in->base_vsync = in->prev_vsync;
        in->delayed_count += 1;
        in->drop_point = 0;
        MP_STATS(vo, "vo-delayed");
    }
    if (in->drop_point > 10)
        in->base_vsync += desync / 10;  // smooth out drift
}