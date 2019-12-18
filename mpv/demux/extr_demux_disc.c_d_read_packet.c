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
struct sh_stream {size_t index; scalar_t__ type; } ;
struct priv {size_t num_streams; scalar_t__ base_dts; scalar_t__ last_dts; double base_time; scalar_t__ is_cdda; struct sh_stream** streams; scalar_t__ seek_reinit; int /*<<< orphan*/  slave; } ;
struct demuxer {struct priv* priv; } ;
struct demux_packet {size_t stream; scalar_t__ pts; scalar_t__ dts; scalar_t__ duration; } ;

/* Variables and functions */
 scalar_t__ DTS_RESET_THRESHOLD ; 
 scalar_t__ MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  MP_TRACE (struct demuxer*,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  MP_WARN (struct demuxer*,char*,...) ; 
 scalar_t__ STREAM_SUB ; 
 int /*<<< orphan*/  add_streams (struct demuxer*) ; 
 struct demux_packet* demux_read_any_packet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  demux_stream_is_selected (struct sh_stream*) ; 
 int /*<<< orphan*/  demux_update (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ fabs (scalar_t__) ; 
 int /*<<< orphan*/  reset_pts (struct demuxer*) ; 
 int /*<<< orphan*/  talloc_free (struct demux_packet*) ; 

__attribute__((used)) static bool d_read_packet(struct demuxer *demuxer, struct demux_packet **out_pkt)
{
    struct priv *p = demuxer->priv;

    struct demux_packet *pkt = demux_read_any_packet(p->slave);
    if (!pkt)
        return false;

    demux_update(p->slave, MP_NOPTS_VALUE);

    if (p->seek_reinit)
        reset_pts(demuxer);

    add_streams(demuxer);
    if (pkt->stream >= p->num_streams) { // out of memory?
        talloc_free(pkt);
        return true;
    }

    struct sh_stream *sh = p->streams[pkt->stream];
    if (!demux_stream_is_selected(sh)) {
        talloc_free(pkt);
        return true;
    }

    pkt->stream = sh->index;

    if (p->is_cdda) {
        *out_pkt = pkt;
        return true;
    }

    MP_TRACE(demuxer, "ipts: %d %f %f\n", sh->type, pkt->pts, pkt->dts);

    if (sh->type == STREAM_SUB) {
        if (p->base_dts == MP_NOPTS_VALUE)
            MP_WARN(demuxer, "subtitle packet along PTS reset\n");
    } else if (pkt->dts != MP_NOPTS_VALUE) {
        // Use the very first DTS to rebase the start time of the MPEG stream
        // to the playback time.
        if (p->base_dts == MP_NOPTS_VALUE)
            p->base_dts = pkt->dts;

        if (p->last_dts == MP_NOPTS_VALUE)
            p->last_dts = pkt->dts;

        if (fabs(p->last_dts - pkt->dts) >= DTS_RESET_THRESHOLD) {
            MP_WARN(demuxer, "PTS discontinuity: %f->%f\n", p->last_dts, pkt->dts);
            p->base_time += p->last_dts - p->base_dts;
            p->base_dts = pkt->dts - pkt->duration;
        }
        p->last_dts = pkt->dts;
    }

    if (p->base_dts != MP_NOPTS_VALUE) {
        double delta = -p->base_dts + p->base_time;
        if (pkt->pts != MP_NOPTS_VALUE)
            pkt->pts += delta;
        if (pkt->dts != MP_NOPTS_VALUE)
            pkt->dts += delta;
    }

    MP_TRACE(demuxer, "opts: %d %f %f\n", sh->type, pkt->pts, pkt->dts);

    *out_pkt = pkt;
    return 1;
}