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
struct mp_recorder_sink {int proper_eof; int discont; scalar_t__ num_packets; int /*<<< orphan*/  packets; TYPE_1__* av_stream; struct mp_recorder* owner; } ;
struct mp_recorder {int dts_warning; } ;
struct demux_packet {scalar_t__ dts; int /*<<< orphan*/  keyframe; } ;
struct TYPE_2__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct mp_recorder*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  MP_TARRAY_APPEND (struct mp_recorder_sink*,int /*<<< orphan*/ ,scalar_t__,struct demux_packet*) ; 
 int /*<<< orphan*/  MP_WARN (struct mp_recorder*,char*) ; 
 scalar_t__ QUEUE_MAX_PACKETS ; 
 int /*<<< orphan*/  check_restart (struct mp_recorder*) ; 
 struct demux_packet* demux_copy_packet (struct demux_packet*) ; 
 int /*<<< orphan*/  mux_packets (struct mp_recorder_sink*,int) ; 

void mp_recorder_feed_packet(struct mp_recorder_sink *rst,
                             struct demux_packet *pkt)
{
    struct mp_recorder *priv = rst->owner;

    if (!pkt) {
        rst->proper_eof = true;
        check_restart(priv);
        mux_packets(rst, false);
        return;
    }

    if (pkt->dts == MP_NOPTS_VALUE && !priv->dts_warning) {
        // No, FFmpeg has no actually usable helpers to generate correct DTS.
        // No, FFmpeg doesn't tell us which formats need DTS at all.
        // No, we can not shut up the FFmpeg warning, which will follow.
        MP_WARN(priv, "Source stream misses DTS on at least some packets!\n"
                      "If the target file format requires DTS, the written\n"
                      "file will be invalid.\n");
        priv->dts_warning = true;
    }

    if (rst->discont && !pkt->keyframe)
        return;
    rst->discont = false;

    if (rst->num_packets >= QUEUE_MAX_PACKETS) {
        MP_ERR(priv, "Stream %d has too many queued packets; dropping.\n",
               rst->av_stream->index);
        return;
    }

    pkt = demux_copy_packet(pkt);
    if (!pkt)
        return;
    MP_TARRAY_APPEND(rst, rst->packets, rst->num_packets, pkt);

    check_restart(priv);
    mux_packets(rst, false);
}