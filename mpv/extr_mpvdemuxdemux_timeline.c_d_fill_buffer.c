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
struct virtual_stream {int eos_packets; TYPE_2__* sh; scalar_t__ selected; } ;
struct segment {scalar_t__ end; scalar_t__ start; size_t num_stream_map; size_t* stream_map; int index; int /*<<< orphan*/  d; } ;
struct priv {int eos_packets; int num_streams; int num_segments; struct virtual_stream** streams; int /*<<< orphan*/  dash; struct segment** segments; struct segment* current; } ;
struct demuxer {struct priv* priv; } ;
struct demux_packet {scalar_t__ pts; size_t stream; int segmented; scalar_t__ start; scalar_t__ end; int pos; scalar_t__ keyframe; scalar_t__ codec; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct TYPE_3__ {scalar_t__ codec; } ;

/* Variables and functions */
 scalar_t__ INT_MAX ; 
 scalar_t__ MP_NOPTS_VALUE ; 
 scalar_t__ STREAM_AUDIO ; 
 scalar_t__ STREAM_VIDEO ; 
 int /*<<< orphan*/  demux_add_packet (TYPE_2__*,struct demux_packet*) ; 
 TYPE_1__* demux_get_stream (int /*<<< orphan*/ ,size_t) ; 
 struct demux_packet* demux_read_any_packet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  switch_segment (struct demuxer*,struct segment*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  talloc_free (struct demux_packet*) ; 

__attribute__((used)) static int d_fill_buffer(struct demuxer *demuxer)
{
    struct priv *p = demuxer->priv;

    if (!p->current)
        switch_segment(demuxer, p->segments[0], 0, 0, true);

    struct segment *seg = p->current;
    if (!seg || !seg->d)
        return 0;

    struct demux_packet *pkt = demux_read_any_packet(seg->d);
    if (!pkt || pkt->pts >= seg->end)
        p->eos_packets += 1;

    // Test for EOF. Do this here to properly run into EOF even if other
    // streams are disabled etc. If it somehow doesn't manage to reach the end
    // after demuxing a high (bit arbitrary) number of packets, assume one of
    // the streams went EOF early.
    bool eos_reached = p->eos_packets > 0;
    if (eos_reached && p->eos_packets < 100) {
        for (int n = 0; n < p->num_streams; n++) {
            struct virtual_stream *vs = p->streams[n];
            if (vs->selected) {
                int max_packets = 0;
                if (vs->sh->type == STREAM_AUDIO)
                    max_packets = 1;
                if (vs->sh->type == STREAM_VIDEO)
                    max_packets = 16;
                eos_reached &= vs->eos_packets >= max_packets;
            }
        }
    }

    if (eos_reached || !pkt) {
        talloc_free(pkt);

        struct segment *next = NULL;
        for (int n = 0; n < p->num_segments - 1; n++) {
            if (p->segments[n] == seg) {
                next = p->segments[n + 1];
                break;
            }
        }
        if (!next)
            return 0;
        switch_segment(demuxer, next, next->start, 0, true);
        return 1; // reader will retry
    }

    if (pkt->stream < 0 || pkt->stream > seg->num_stream_map)
        goto drop;

    if (!p->dash) {
        pkt->segmented = true;
        if (!pkt->codec)
            pkt->codec = demux_get_stream(seg->d, pkt->stream)->codec;
        if (pkt->start == MP_NOPTS_VALUE || pkt->start < seg->start)
            pkt->start = seg->start;
        if (pkt->end == MP_NOPTS_VALUE || pkt->end > seg->end)
            pkt->end = seg->end;
    }

    pkt->stream = seg->stream_map[pkt->stream];
    if (pkt->stream < 0)
        goto drop;

    // for refresh seeks, demux.c prefers monotonically increasing packet pos
    // since the packet pos is meaningless anyway for timeline, use it
    if (pkt->pos >= 0)
        pkt->pos |= (seg->index & 0x7FFFULL) << 48;

    struct virtual_stream *vs = p->streams[pkt->stream];

    if (pkt->pts != MP_NOPTS_VALUE && pkt->pts >= seg->end) {
        // Trust the keyframe flag. Might not always be a good idea, but will
        // be sufficient at least with mkv. The problem is that this flag is
        // not well-defined in libavformat and is container-dependent.
        if (pkt->keyframe || vs->eos_packets == INT_MAX) {
            vs->eos_packets = INT_MAX;
            goto drop;
        } else {
            vs->eos_packets += 1;
        }
    }

    demux_add_packet(vs->sh, pkt);
    return 1;

drop:
    talloc_free(pkt);
    return 1;
}