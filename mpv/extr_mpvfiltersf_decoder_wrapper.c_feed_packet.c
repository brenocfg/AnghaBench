#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ type; struct demux_packet* data; } ;
struct TYPE_11__ {scalar_t__ recorder_sink; scalar_t__ attempt_framedrops; } ;
struct priv {double start_pts; double start; int has_broken_packet_pts; double first_packet_pdts; int packets_without_output; TYPE_5__ packet; TYPE_3__* decoder; TYPE_2__* codec; TYPE_1__ public; struct demux_packet* new_segment; int /*<<< orphan*/  f; int /*<<< orphan*/  demux; } ;
struct demux_packet {double pts; double dts; } ;
struct TYPE_14__ {int /*<<< orphan*/ * pins; } ;
struct TYPE_13__ {TYPE_4__* f; int /*<<< orphan*/  (* control ) (TYPE_4__*,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  avi_dts; } ;

/* Variables and functions */
 TYPE_5__ MP_EOF_FRAME ; 
 int /*<<< orphan*/  MP_ERR (struct priv*,char*) ; 
 scalar_t__ MP_FRAME_EOF ; 
 scalar_t__ MP_FRAME_PACKET ; 
 double MP_NOPTS_VALUE ; 
 TYPE_5__ MP_NO_FRAME ; 
 int /*<<< orphan*/  VDCTRL_SET_FRAMEDROP ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ is_new_segment (struct priv*,TYPE_5__) ; 
 int /*<<< orphan*/  mp_filter_internal_mark_failed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_frame_unref (TYPE_5__*) ; 
 int /*<<< orphan*/  mp_pin_in_needs_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_pin_in_write (int /*<<< orphan*/ ,TYPE_5__) ; 
 TYPE_5__ mp_pin_out_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_recorder_feed_packet (scalar_t__,struct demux_packet*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void feed_packet(struct priv *p)
{
    if (!p->decoder || !mp_pin_in_needs_data(p->decoder->f->pins[0]))
        return;

    if (!p->packet.type && !p->new_segment) {
        p->packet = mp_pin_out_read(p->demux);
        if (!p->packet.type)
            return;
        if (p->packet.type != MP_FRAME_EOF && p->packet.type != MP_FRAME_PACKET) {
            MP_ERR(p, "invalid frame type from demuxer\n");
            mp_frame_unref(&p->packet);
            mp_filter_internal_mark_failed(p->f);
            return;
        }
    }

    // Flush current data if the packet is a new segment.
    if (is_new_segment(p, p->packet)) {
        assert(!p->new_segment);
        p->new_segment = p->packet.data;
        p->packet = MP_EOF_FRAME;
    }

    assert(p->packet.type == MP_FRAME_PACKET || p->packet.type == MP_FRAME_EOF);
    struct demux_packet *packet = p->packet.data;

    // For video framedropping, including parts of the hr-seek logic.
    if (p->decoder->control) {
        double start_pts = p->start_pts;
        if (p->start != MP_NOPTS_VALUE && (start_pts == MP_NOPTS_VALUE ||
                                           p->start > start_pts))
            start_pts = p->start;

        int framedrop_type = 0;

        if (p->public.attempt_framedrops)
            framedrop_type = 1;

        if (start_pts != MP_NOPTS_VALUE && packet &&
            packet->pts < start_pts - .005 && !p->has_broken_packet_pts)
            framedrop_type = 2;

        p->decoder->control(p->decoder->f, VDCTRL_SET_FRAMEDROP, &framedrop_type);
    }

    if (p->public.recorder_sink)
        mp_recorder_feed_packet(p->public.recorder_sink, packet);

    double pkt_pts = packet ? packet->pts : MP_NOPTS_VALUE;
    double pkt_dts = packet ? packet->dts : MP_NOPTS_VALUE;

    if (pkt_pts == MP_NOPTS_VALUE)
        p->has_broken_packet_pts = 1;

    if (packet && packet->dts == MP_NOPTS_VALUE && !p->codec->avi_dts)
        packet->dts = packet->pts;

    double pkt_pdts = pkt_pts == MP_NOPTS_VALUE ? pkt_dts : pkt_pts;
    if (p->first_packet_pdts == MP_NOPTS_VALUE)
        p->first_packet_pdts = pkt_pdts;

    mp_pin_in_write(p->decoder->f->pins[0], p->packet);
    p->packet = MP_NO_FRAME;

    p->packets_without_output += 1;
}