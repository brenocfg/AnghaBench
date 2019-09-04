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
struct demux_queue {int num_index; scalar_t__ index_distance; struct demux_packet** index; } ;
struct demux_packet {scalar_t__ kf_seek_pts; scalar_t__ keyframe; } ;

/* Variables and functions */
 int MAX_INDEX_ENTRIES ; 
 scalar_t__ MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void add_index_entry(struct demux_queue *queue, struct demux_packet *dp)
{
    assert(dp->keyframe && dp->kf_seek_pts != MP_NOPTS_VALUE);

    if (queue->num_index) {
        double prev = queue->index[queue->num_index - 1]->kf_seek_pts;
        if (dp->kf_seek_pts < prev + queue->index_distance)
            return;
    }

    if (queue->num_index == MAX_INDEX_ENTRIES) {
        for (int n = 0; n < MAX_INDEX_ENTRIES / 2; n++)
            queue->index[n] = queue->index[n * 2];
        queue->num_index = MAX_INDEX_ENTRIES / 2;
        queue->index_distance *= 2;
    }

    queue->index[queue->num_index++] = dp;
}