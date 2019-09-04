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
struct TYPE_3__ {int const pix_fmt; } ;
struct TYPE_4__ {int hwdec_request_reinit; int hwdec_failed; TYPE_1__ hwdec; int /*<<< orphan*/  use_hwdec; } ;
typedef  TYPE_2__ vd_ffmpeg_ctx ;
struct mp_filter {TYPE_2__* priv; } ;
struct AVCodecContext {int /*<<< orphan*/  profile; int /*<<< orphan*/  codec_id; struct mp_filter* opaque; } ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;

/* Variables and functions */
 int const AV_PIX_FMT_NONE ; 
 int /*<<< orphan*/  MP_VERBOSE (struct mp_filter*,char*,...) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 char const* av_get_pix_fmt_name (int const) ; 
 int avcodec_default_get_format (struct AVCodecContext*,int const*) ; 
 char* avcodec_profile_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ init_generic_hwaccel (struct mp_filter*,int const) ; 

__attribute__((used)) static enum AVPixelFormat get_format_hwdec(struct AVCodecContext *avctx,
                                           const enum AVPixelFormat *fmt)
{
    struct mp_filter *vd = avctx->opaque;
    vd_ffmpeg_ctx *ctx = vd->priv;

    MP_VERBOSE(vd, "Pixel formats supported by decoder:");
    for (int i = 0; fmt[i] != AV_PIX_FMT_NONE; i++)
        MP_VERBOSE(vd, " %s", av_get_pix_fmt_name(fmt[i]));
    MP_VERBOSE(vd, "\n");

    const char *profile = avcodec_profile_name(avctx->codec_id, avctx->profile);
    MP_VERBOSE(vd, "Codec profile: %s (0x%x)\n", profile ? profile : "unknown",
               avctx->profile);

    assert(ctx->use_hwdec);

    ctx->hwdec_request_reinit |= ctx->hwdec_failed;
    ctx->hwdec_failed = false;

    enum AVPixelFormat select = AV_PIX_FMT_NONE;
    for (int i = 0; fmt[i] != AV_PIX_FMT_NONE; i++) {
        if (ctx->hwdec.pix_fmt == fmt[i]) {
            if (init_generic_hwaccel(vd, fmt[i]) < 0)
                break;
            select = fmt[i];
            break;
        }
    }

    if (select == AV_PIX_FMT_NONE) {
        ctx->hwdec_failed = true;
        select = avcodec_default_get_format(avctx, fmt);
    }

    const char *name = av_get_pix_fmt_name(select);
    MP_VERBOSE(vd, "Requesting pixfmt '%s' from decoder.\n", name ? name : "-");
    return select;
}