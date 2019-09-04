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
struct demux_stream {struct demux_packet* reader_head; struct demux_internal* in; } ;
struct demux_queue {double index_distance; int correct_dts; int correct_pos; int last_pos; int is_eof; int is_bof; void* keyframe_end_pts; void* keyframe_pts; int /*<<< orphan*/ * keyframe_latest; void* last_dts; void* last_ts; scalar_t__ num_index; void* last_pruned; void* seek_end; void* seek_start; int /*<<< orphan*/ * next_prune_target; int /*<<< orphan*/ * tail; struct demux_packet* head; struct demux_stream* ds; } ;
struct demux_packet {struct demux_packet* next; } ;
struct demux_internal {int /*<<< orphan*/  total_bytes; } ;

/* Variables and functions */
 void* MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ demux_packet_estimate_total_size (struct demux_packet*) ; 
 int /*<<< orphan*/  talloc_free (struct demux_packet*) ; 

__attribute__((used)) static void clear_queue(struct demux_queue *queue)
{
    struct demux_stream *ds = queue->ds;
    struct demux_internal *in = ds->in;

    struct demux_packet *dp = queue->head;
    while (dp) {
        struct demux_packet *dn = dp->next;
        in->total_bytes -= demux_packet_estimate_total_size(dp);
        assert(ds->reader_head != dp);
        talloc_free(dp);
        dp = dn;
    }
    queue->head = queue->tail = NULL;
    queue->next_prune_target = NULL;
    queue->keyframe_latest = NULL;
    queue->seek_start = queue->seek_end = queue->last_pruned = MP_NOPTS_VALUE;

    queue->num_index = 0;
    queue->index_distance = 1.0;

    queue->correct_dts = queue->correct_pos = true;
    queue->last_pos = -1;
    queue->last_ts = queue->last_dts = MP_NOPTS_VALUE;
    queue->keyframe_latest = NULL;
    queue->keyframe_pts = queue->keyframe_end_pts = MP_NOPTS_VALUE;

    queue->is_eof = false;
    queue->is_bof = false;
}