#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct demux_queue {struct demux_packet* head; TYPE_2__* ds; } ;
struct demux_packet {int /*<<< orphan*/  keyframe; struct demux_packet* next; } ;
struct TYPE_4__ {TYPE_1__* sh; } ;
struct TYPE_3__ {scalar_t__ seek_preroll; } ;

/* Variables and functions */
 double MP_NOPTS_VALUE ; 
 int SEEK_FORWARD ; 
 struct demux_packet* compute_keyframe_times (struct demux_packet*,double*,int /*<<< orphan*/ *) ; 
 struct demux_packet* search_index (struct demux_queue*,double) ; 

__attribute__((used)) static struct demux_packet *find_seek_target(struct demux_queue *queue,
                                             double pts, int flags)
{
    pts -= queue->ds->sh->seek_preroll;

    struct demux_packet *start = search_index(queue, pts);
    if (!start)
        start = queue->head;

    struct demux_packet *target = NULL;
    struct demux_packet *next = NULL;
    for (struct demux_packet *dp = start; dp; dp = next) {
        next = dp->next;
        if (!dp->keyframe)
            continue;

        double range_pts;
        next = compute_keyframe_times(dp, &range_pts, NULL);

        if (range_pts == MP_NOPTS_VALUE)
            continue;

        if (flags & SEEK_FORWARD) {
            // Stop on the first packet that is >= pts.
            if (target)
                break;
            if (range_pts < pts)
                continue;
        } else {
            // Stop before the first packet that is > pts.
            // This still returns a packet with > pts if there's no better one.
            if (target && range_pts > pts)
                break;
        }

        target = dp;
    }

    return target;
}