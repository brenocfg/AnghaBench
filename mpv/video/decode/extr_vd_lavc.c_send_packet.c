#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int num_sent_packets; int /*<<< orphan*/  sent_packets; TYPE_1__* opts; scalar_t__ hw_probing; int /*<<< orphan*/  codec_timebase; TYPE_3__* avctx; scalar_t__ hwdec_failed; struct demux_packet** requeue_packets; scalar_t__ num_requeue_packets; } ;
typedef  TYPE_2__ vd_ffmpeg_ctx ;
struct mp_filter {TYPE_2__* priv; } ;
struct demux_packet {int dummy; } ;
struct TYPE_8__ {scalar_t__ skip_frame; } ;
struct TYPE_6__ {int software_fallback; } ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AVDISCARD_ALL ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  MP_TARRAY_APPEND (TYPE_2__*,int /*<<< orphan*/ ,int,struct demux_packet*) ; 
 int avcodec_send_packet (TYPE_3__*,int /*<<< orphan*/ *) ; 
 struct demux_packet* demux_copy_packet (struct demux_packet*) ; 
 int /*<<< orphan*/  handle_err (struct mp_filter*) ; 
 int /*<<< orphan*/  mp_set_av_packet (int /*<<< orphan*/ *,struct demux_packet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_decoding (struct mp_filter*) ; 

__attribute__((used)) static int send_packet(struct mp_filter *vd, struct demux_packet *pkt)
{
    vd_ffmpeg_ctx *ctx = vd->priv;
    AVCodecContext *avctx = ctx->avctx;

    if (ctx->num_requeue_packets && ctx->requeue_packets[0] != pkt)
        return AVERROR(EAGAIN); // cannot consume the packet

    if (ctx->hwdec_failed)
        return AVERROR(EAGAIN);

    if (!ctx->avctx)
        return AVERROR_EOF;

    prepare_decoding(vd);

    if (avctx->skip_frame == AVDISCARD_ALL)
        return 0;

    AVPacket avpkt;
    mp_set_av_packet(&avpkt, pkt, &ctx->codec_timebase);

    int ret = avcodec_send_packet(avctx, pkt ? &avpkt : NULL);
    if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
        return ret;

    if (ctx->hw_probing && ctx->num_sent_packets < 32 &&
        ctx->opts->software_fallback <= 32)
    {
        pkt = pkt ? demux_copy_packet(pkt) : NULL;
        MP_TARRAY_APPEND(ctx, ctx->sent_packets, ctx->num_sent_packets, pkt);
    }

    if (ret < 0)
        handle_err(vd);
    return ret;
}