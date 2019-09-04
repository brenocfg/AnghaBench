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
struct vo_vsync_info {void* last_queue_display_time; } ;
struct vo_internal {int num_successive_vsyncs; int num_vsync_samples; int* vsync_samples; int num_total_vsync_samples; int vsync_interval; double estimated_vsync_interval; int estimated_vsync_jitter; void* base_vsync; scalar_t__ drop_point; int /*<<< orphan*/  expecting_vsync; void* prev_vsync; } ;
struct vo {struct vo_internal* in; } ;
typedef  void* int64_t ;

/* Variables and functions */
 int MAX_VSYNC_SAMPLES ; 
 scalar_t__ MPMIN (scalar_t__,int) ; 
 int /*<<< orphan*/  MP_STATS (struct vo*,char*,int) ; 
 int /*<<< orphan*/  MP_TARRAY_INSERT_AT (struct vo_internal*,int*,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  check_estimated_display_fps (struct vo*) ; 
 int /*<<< orphan*/  reset_vsync_timings (struct vo*) ; 
 int /*<<< orphan*/  vsync_skip_detection (struct vo*) ; 
 int vsync_stddef (struct vo*,int) ; 

__attribute__((used)) static void update_vsync_timing_after_swap(struct vo *vo,
                                           struct vo_vsync_info *vsync)
{
    struct vo_internal *in = vo->in;

    int64_t vsync_time = vsync->last_queue_display_time;
    int64_t prev_vsync = in->prev_vsync;
    in->prev_vsync = vsync_time;

    if (!in->expecting_vsync) {
        reset_vsync_timings(vo);
        return;
    }

    in->num_successive_vsyncs++;
    if (in->num_successive_vsyncs <= 2)
        return;

    if (in->num_vsync_samples >= MAX_VSYNC_SAMPLES)
        in->num_vsync_samples -= 1;
    MP_TARRAY_INSERT_AT(in, in->vsync_samples, in->num_vsync_samples, 0,
                        vsync_time - prev_vsync);
    in->drop_point = MPMIN(in->drop_point + 1, in->num_vsync_samples);
    in->num_total_vsync_samples += 1;
    if (in->base_vsync) {
        in->base_vsync += in->vsync_interval;
    } else {
        in->base_vsync = vsync_time;
    }

    double avg = 0;
    for (int n = 0; n < in->num_vsync_samples; n++)
        avg += in->vsync_samples[n];
    in->estimated_vsync_interval = avg / in->num_vsync_samples;
    in->estimated_vsync_jitter =
        vsync_stddef(vo, in->vsync_interval) / in->vsync_interval;

    check_estimated_display_fps(vo);
    vsync_skip_detection(vo);

    MP_STATS(vo, "value %f jitter", in->estimated_vsync_jitter);
    MP_STATS(vo, "value %f vsync-diff", in->vsync_samples[0] / 1e6);
}