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
struct demux_queue {int is_bof; int /*<<< orphan*/ * tail; struct demux_packet* head; scalar_t__ num_index; struct demux_packet** index; TYPE_2__* ds; struct demux_packet* keyframe_latest; struct demux_packet* next_prune_target; } ;
struct demux_packet {struct demux_packet* next; } ;
struct TYPE_4__ {TYPE_1__* in; struct demux_packet* reader_head; } ;
struct TYPE_3__ {int /*<<< orphan*/  total_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_REMOVE_AT (struct demux_packet**,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ demux_packet_estimate_total_size (struct demux_packet*) ; 
 int /*<<< orphan*/  talloc_free (struct demux_packet*) ; 

__attribute__((used)) static void remove_head_packet(struct demux_queue *queue)
{
    struct demux_packet *dp = queue->head;

    assert(queue->ds->reader_head != dp);
    if (queue->next_prune_target == dp)
        queue->next_prune_target = NULL;
    if (queue->keyframe_latest == dp)
        queue->keyframe_latest = NULL;
    queue->is_bof = false;

    queue->ds->in->total_bytes -= demux_packet_estimate_total_size(dp);

    if (queue->num_index && queue->index[0] == dp)
        MP_TARRAY_REMOVE_AT(queue->index, queue->num_index, 0);

    queue->head = dp->next;
    if (!queue->head)
        queue->tail = NULL;

    talloc_free(dp);
}