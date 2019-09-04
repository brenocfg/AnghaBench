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
struct TYPE_3__ {int /*<<< orphan*/  method_name; scalar_t__ copying; } ;
struct TYPE_4__ {int num_sent_packets; int num_requeue_packets; scalar_t__ num_delay_queue; scalar_t__ max_delay_queue; int hwdec_notified; int hw_probing; struct demux_packet** sent_packets; TYPE_1__ hwdec; scalar_t__ use_hwdec; scalar_t__ hwdec_requested; scalar_t__ hwdec_fail_count; int /*<<< orphan*/  hwdec_swpool; struct mp_image** delay_queue; struct demux_packet** requeue_packets; scalar_t__ hwdec_failed; } ;
typedef  TYPE_2__ vd_ffmpeg_ctx ;
struct mp_image {scalar_t__ hwctx; } ;
struct mp_frame {int dummy; } ;
struct mp_filter {TYPE_2__* priv; } ;
struct demux_packet {int dummy; } ;

/* Variables and functions */
 scalar_t__ INT_MAX ; 
 struct mp_frame MAKE_FRAME (int /*<<< orphan*/ ,struct mp_image*) ; 
 int /*<<< orphan*/  MP_ERR (struct mp_filter*,char*) ; 
 int /*<<< orphan*/  MP_FRAME_VIDEO ; 
 int /*<<< orphan*/  MP_INFO (struct mp_filter*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_TARRAY_REMOVE_AT (struct mp_image**,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct mp_filter*,char*) ; 
 int decode_frame (struct mp_filter*) ; 
 int /*<<< orphan*/  force_fallback (struct mp_filter*) ; 
 int /*<<< orphan*/  handle_err (struct mp_filter*) ; 
 struct mp_image* mp_image_hw_download (struct mp_image*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_image_unrefp (struct mp_image**) ; 
 struct mp_image* mp_img_swap_to_native (struct mp_image*) ; 
 int /*<<< orphan*/  send_queued (struct mp_filter*) ; 
 int /*<<< orphan*/  talloc_free (struct demux_packet*) ; 

__attribute__((used)) static bool receive_frame(struct mp_filter *vd, struct mp_frame *out_frame)
{
    vd_ffmpeg_ctx *ctx = vd->priv;

    bool progress = decode_frame(vd);

    if (ctx->hwdec_failed) {
        // Failed hardware decoding? Try again in software.
        struct demux_packet **pkts = ctx->sent_packets;
        int num_pkts = ctx->num_sent_packets;
        ctx->sent_packets = NULL;
        ctx->num_sent_packets = 0;

        force_fallback(vd);

        ctx->requeue_packets = pkts;
        ctx->num_requeue_packets = num_pkts;

        send_queued(vd);
        progress = decode_frame(vd);
    }

    if (!ctx->num_delay_queue)
        return progress;

    if (ctx->num_delay_queue <= ctx->max_delay_queue && progress)
        return true;

    struct mp_image *res = ctx->delay_queue[0];
    MP_TARRAY_REMOVE_AT(ctx->delay_queue, ctx->num_delay_queue, 0);

    res = res ? mp_img_swap_to_native(res) : NULL;
    if (!res)
        return progress;

    if (ctx->use_hwdec && ctx->hwdec.copying && res->hwctx) {
        struct mp_image *sw = mp_image_hw_download(res, ctx->hwdec_swpool);
        mp_image_unrefp(&res);
        res = sw;
        if (!res) {
            MP_ERR(vd, "Could not copy back hardware decoded frame.\n");
            ctx->hwdec_fail_count = INT_MAX - 1; // force fallback
            handle_err(vd);
            return true;
        }
    }

    if (!ctx->hwdec_notified && ctx->hwdec_requested) {
        if (ctx->use_hwdec) {
            MP_INFO(vd, "Using hardware decoding (%s).\n",
                    ctx->hwdec.method_name);
        } else {
            MP_VERBOSE(vd, "Using software decoding.\n");
        }
        ctx->hwdec_notified = true;
    }

    if (ctx->hw_probing) {
        for (int n = 0; n < ctx->num_sent_packets; n++)
            talloc_free(ctx->sent_packets[n]);
        ctx->num_sent_packets = 0;
        ctx->hw_probing = false;
    }

    *out_frame = MAKE_FRAME(MP_FRAME_VIDEO, res);
    return true;
}