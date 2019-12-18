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
struct demux_stream {scalar_t__ type; scalar_t__ selected; } ;
struct demux_queue {int dummy; } ;
struct demux_packet {int dummy; } ;
struct demux_internal {int num_streams; TYPE_1__** streams; } ;
struct demux_cached_range {struct demux_queue** streams; } ;
struct TYPE_2__ {struct demux_stream* ds; } ;

/* Variables and functions */
 double MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  MP_VERBOSE (struct demux_internal*,char*,double,double) ; 
 int SEEK_FORWARD ; 
 int SEEK_HR ; 
 scalar_t__ STREAM_VIDEO ; 
 int /*<<< orphan*/  compute_keyframe_times (struct demux_packet*,double*,int /*<<< orphan*/ *) ; 
 struct demux_packet* find_seek_target (struct demux_queue*,double,int) ; 

__attribute__((used)) static void adjust_cache_seek_target(struct demux_internal *in,
                                     struct demux_cached_range *range,
                                     double *pts, int *flags)
{
    if (*flags & SEEK_HR)
        return;

    for (int n = 0; n < in->num_streams; n++) {
        struct demux_stream *ds = in->streams[n]->ds;
        struct demux_queue *queue = range->streams[n];
        if (ds->selected && ds->type == STREAM_VIDEO) {
            struct demux_packet *target = find_seek_target(queue, *pts, *flags);
            if (target) {
                double target_pts;
                compute_keyframe_times(target, &target_pts, NULL);
                if (target_pts != MP_NOPTS_VALUE) {
                    MP_VERBOSE(in, "adjust seek target %f -> %f\n",
                               *pts, target_pts);
                    // (We assume the find_seek_target() call will return
                    // the same target for the video stream.)
                    *pts = target_pts;
                    *flags &= ~SEEK_FORWARD;
                }
            }
            break;
        }
    }
}