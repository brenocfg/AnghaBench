#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mp_packet_tags {int dummy; } ;
struct demux_stream {int eof; int attached_picture_added; size_t fw_bytes; scalar_t__ last_ret_pos; double base_ts; double last_br_ts; int bitrate; double last_br_bytes; TYPE_3__* in; struct mp_packet_tags* tags_reader; struct mp_packet_tags* tags_init; void* last_ret_dts; int /*<<< orphan*/  fw_packs; struct demux_packet* reader_head; TYPE_1__* sh; } ;
struct demux_packet {scalar_t__ pos; struct mp_packet_tags* metadata; void* end; void* start; scalar_t__ segmented; void* dts; void* pts; scalar_t__ len; scalar_t__ keyframe; struct demux_packet* next; int /*<<< orphan*/  stream; } ;
struct TYPE_6__ {size_t fw_bytes; int /*<<< orphan*/  wakeup_cb_ctx; int /*<<< orphan*/  (* wakeup_cb ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  events; int /*<<< orphan*/  ts_offset; TYPE_2__* d_user; scalar_t__ blocked; } ;
struct TYPE_5__ {scalar_t__ filepos; } ;
struct TYPE_4__ {int /*<<< orphan*/  index; struct demux_packet* attached_picture; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEMUX_EVENT_METADATA ; 
 void* MP_ADD_PTS (void*,int /*<<< orphan*/ ) ; 
 double MP_NOPTS_VALUE ; 
 double PTS_OR_DEF (void*,void*) ; 
 int /*<<< orphan*/  abort () ; 
 struct demux_packet* demux_copy_packet (struct demux_packet*) ; 
 size_t demux_packet_estimate_total_size (struct demux_packet*) ; 
 int /*<<< orphan*/  mp_packet_tags_setref (struct mp_packet_tags**,struct mp_packet_tags*) ; 
 int /*<<< orphan*/  prune_old_packets (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct demux_packet *dequeue_packet(struct demux_stream *ds)
{
    if (ds->sh->attached_picture) {
        ds->eof = true;
        if (ds->attached_picture_added)
            return NULL;
        ds->attached_picture_added = true;
        struct demux_packet *pkt = demux_copy_packet(ds->sh->attached_picture);
        if (!pkt)
            abort();
        pkt->stream = ds->sh->index;
        return pkt;
    }
    if (!ds->reader_head || ds->in->blocked)
        return NULL;
    struct demux_packet *pkt = ds->reader_head;
    ds->reader_head = pkt->next;

    // Update cached packet queue state.
    ds->fw_packs--;
    size_t bytes = demux_packet_estimate_total_size(pkt);
    ds->fw_bytes -= bytes;
    ds->in->fw_bytes -= bytes;

    ds->last_ret_pos = pkt->pos;
    ds->last_ret_dts = pkt->dts;

    // The returned packet is mutated etc. and will be owned by the user.
    pkt = demux_copy_packet(pkt);
    if (!pkt)
        abort();
    pkt->next = NULL;

    double ts = PTS_OR_DEF(pkt->dts, pkt->pts);
    if (ts != MP_NOPTS_VALUE)
        ds->base_ts = ts;

    if (pkt->keyframe && ts != MP_NOPTS_VALUE) {
        // Update bitrate - only at keyframe points, because we use the
        // (possibly) reordered packet timestamps instead of realtime.
        double d = ts - ds->last_br_ts;
        if (ds->last_br_ts == MP_NOPTS_VALUE || d < 0) {
            ds->bitrate = -1;
            ds->last_br_ts = ts;
            ds->last_br_bytes = 0;
        } else if (d >= 0.5) { // a window of least 500ms for UI purposes
            ds->bitrate = ds->last_br_bytes / d;
            ds->last_br_ts = ts;
            ds->last_br_bytes = 0;
        }
    }
    ds->last_br_bytes += pkt->len;

    // This implies this function is actually called from "the" user thread.
    if (pkt->pos >= ds->in->d_user->filepos)
        ds->in->d_user->filepos = pkt->pos;

    pkt->pts = MP_ADD_PTS(pkt->pts, ds->in->ts_offset);
    pkt->dts = MP_ADD_PTS(pkt->dts, ds->in->ts_offset);

    if (pkt->segmented) {
        pkt->start = MP_ADD_PTS(pkt->start, ds->in->ts_offset);
        pkt->end = MP_ADD_PTS(pkt->end, ds->in->ts_offset);
    }

    // Apply timed metadata when packet is returned to user.
    // (The tags_init thing is a microopt. to not do refcounting for sane files.)
    struct mp_packet_tags *metadata = pkt->metadata;
    if (!metadata)
        metadata = ds->tags_init;
    if (metadata != ds->tags_reader) {
        mp_packet_tags_setref(&ds->tags_reader, metadata);
        ds->in->events |= DEMUX_EVENT_METADATA;
        if (ds->in->wakeup_cb)
            ds->in->wakeup_cb(ds->in->wakeup_cb_ctx);
    }

    prune_old_packets(ds->in);
    return pkt;
}