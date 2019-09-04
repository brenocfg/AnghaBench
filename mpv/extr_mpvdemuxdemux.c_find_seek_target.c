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
struct demux_queue {int num_index; struct demux_packet** index; struct demux_packet* head; } ;
struct demux_packet {double kf_seek_pts; int /*<<< orphan*/  keyframe; struct demux_packet* next; } ;

/* Variables and functions */
 double MP_NOPTS_VALUE ; 
 int SEEK_FORWARD ; 

__attribute__((used)) static struct demux_packet *find_seek_target(struct demux_queue *queue,
                                             double pts, int flags)
{
    struct demux_packet *start = queue->head;
    for (int n = 0; n < queue->num_index; n++) {
        if (queue->index[n]->kf_seek_pts > pts)
            break;
        start = queue->index[n];
    }

    struct demux_packet *target = NULL;
    double target_diff = MP_NOPTS_VALUE;
    for (struct demux_packet *dp = start; dp; dp = dp->next) {
        double range_pts = dp->kf_seek_pts;
        if (!dp->keyframe || range_pts == MP_NOPTS_VALUE)
            continue;

        double diff = range_pts - pts;
        if (flags & SEEK_FORWARD) {
            diff = -diff;
            if (diff > 0)
                continue;
        }
        if (target) {
            if (diff <= 0) {
                if (target_diff <= 0 && diff <= target_diff)
                    continue;
            } else if (diff >= target_diff)
                continue;
        }
        target_diff = diff;
        target = dp;
        if (range_pts > pts)
            break;
    }

    return target;
}