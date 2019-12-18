#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct spdifContext {int out_buffer_len; int sstride; int /*<<< orphan*/  out_buffer; int /*<<< orphan*/  pool; int /*<<< orphan*/  fmt; TYPE_4__* lavf_ctx; } ;
struct mp_frame {scalar_t__ type; struct demux_packet* data; } ;
struct mp_filter {int /*<<< orphan*/ * ppins; struct spdifContext* priv; } ;
struct mp_aframe {int dummy; } ;
struct demux_packet {double pts; } ;
struct TYPE_7__ {int /*<<< orphan*/  pb; } ;
struct TYPE_6__ {scalar_t__ dts; scalar_t__ pts; } ;
typedef  TYPE_1__ AVPacket ;

/* Variables and functions */
 int /*<<< orphan*/  AVUNERROR (int) ; 
 struct mp_frame MAKE_FRAME (int /*<<< orphan*/ ,struct mp_aframe*) ; 
 int /*<<< orphan*/  MP_ERR (struct mp_filter*,char*,...) ; 
 int /*<<< orphan*/  MP_FRAME_AUDIO ; 
 scalar_t__ MP_FRAME_EOF ; 
 scalar_t__ MP_FRAME_PACKET ; 
 int /*<<< orphan*/  TA_FREEP (struct mp_aframe**) ; 
 int av_write_frame (TYPE_4__*,TYPE_1__*) ; 
 int /*<<< orphan*/  avio_flush (int /*<<< orphan*/ ) ; 
 scalar_t__ init_filter (struct mp_filter*,TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ ** mp_aframe_get_data_rw (struct mp_aframe*) ; 
 struct mp_aframe* mp_aframe_new_ref (int /*<<< orphan*/ ) ; 
 scalar_t__ mp_aframe_pool_allocate (int /*<<< orphan*/ ,struct mp_aframe*,int) ; 
 int /*<<< orphan*/  mp_aframe_set_pts (struct mp_aframe*,double) ; 
 int /*<<< orphan*/  mp_filter_internal_mark_failed (struct mp_filter*) ; 
 int /*<<< orphan*/  mp_pin_can_transfer_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_pin_in_write (int /*<<< orphan*/ ,struct mp_frame) ; 
 struct mp_frame mp_pin_out_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_set_av_packet (TYPE_1__*,struct demux_packet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (struct demux_packet*) ; 

__attribute__((used)) static void process(struct mp_filter *da)
{
    struct spdifContext *spdif_ctx = da->priv;

    if (!mp_pin_can_transfer_data(da->ppins[1], da->ppins[0]))
        return;

    struct mp_frame inframe = mp_pin_out_read(da->ppins[0]);
    if (inframe.type == MP_FRAME_EOF) {
        mp_pin_in_write(da->ppins[1], inframe);
        return;
    } else if (inframe.type != MP_FRAME_PACKET) {
        if (inframe.type) {
            MP_ERR(da, "unknown frame type\n");
            mp_filter_internal_mark_failed(da);
        }
        return;
    }

    struct demux_packet *mpkt = inframe.data;
    struct mp_aframe *out = NULL;
    double pts = mpkt->pts;

    AVPacket pkt;
    mp_set_av_packet(&pkt, mpkt, NULL);
    pkt.pts = pkt.dts = 0;
    if (!spdif_ctx->lavf_ctx) {
        if (init_filter(da, &pkt) < 0)
            goto done;
    }
    spdif_ctx->out_buffer_len  = 0;
    int ret = av_write_frame(spdif_ctx->lavf_ctx, &pkt);
    avio_flush(spdif_ctx->lavf_ctx->pb);
    if (ret < 0) {
        MP_ERR(da, "spdif mux error: '%s'\n", mp_strerror(AVUNERROR(ret)));
        goto done;
    }

    out = mp_aframe_new_ref(spdif_ctx->fmt);
    int samples = spdif_ctx->out_buffer_len / spdif_ctx->sstride;
    if (mp_aframe_pool_allocate(spdif_ctx->pool, out, samples) < 0) {
        TA_FREEP(&out);
        goto done;
    }

    uint8_t **data = mp_aframe_get_data_rw(out);
    if (!data) {
        TA_FREEP(&out);
        goto done;
    }

    memcpy(data[0], spdif_ctx->out_buffer, spdif_ctx->out_buffer_len);
    mp_aframe_set_pts(out, pts);

done:
    talloc_free(mpkt);
    if (out) {
        mp_pin_in_write(da->ppins[1], MAKE_FRAME(MP_FRAME_AUDIO, out));
    } else {
        mp_filter_internal_mark_failed(da);
    }
}