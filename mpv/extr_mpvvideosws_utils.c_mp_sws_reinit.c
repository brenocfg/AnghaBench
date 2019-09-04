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
struct TYPE_2__ {scalar_t__ levels; int /*<<< orphan*/  space; } ;
struct mp_image_params {int w; int h; TYPE_1__ color; int /*<<< orphan*/  imgfmt; scalar_t__ p_h; scalar_t__ p_w; } ;
struct mp_sws_context {int flags; int supports_csp; int force_reload; struct mp_sws_context* cached; int /*<<< orphan*/  dst_filter; int /*<<< orphan*/  src_filter; int /*<<< orphan*/  sws; int /*<<< orphan*/  saturation; int /*<<< orphan*/  contrast; int /*<<< orphan*/  brightness; int /*<<< orphan*/ * params; struct mp_image_params dst; struct mp_image_params src; } ;
struct mp_imgfmt_desc {int flags; int /*<<< orphan*/  id; } ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;

/* Variables and functions */
 int AV_PIX_FMT_NONE ; 
 scalar_t__ MP_CSP_LEVELS_PC ; 
 int /*<<< orphan*/  MP_ERR (struct mp_sws_context*,char*,int /*<<< orphan*/ ) ; 
 int MP_IMGFLAG_YUV ; 
 int /*<<< orphan*/  av_opt_set_double (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_opt_set_int (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ cache_valid (struct mp_sws_context*) ; 
 int imgfmt2pixfmt (int /*<<< orphan*/ ) ; 
 int mp_csp_to_sws_colorspace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_image_params_guess_csp (struct mp_image_params*) ; 
 struct mp_imgfmt_desc mp_imgfmt_get_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_imgfmt_to_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sws_alloc_context () ; 
 int /*<<< orphan*/  sws_freeContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sws_getCoefficients (int) ; 
 scalar_t__ sws_init_context (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sws_isSupportedInput (int) ; 
 int sws_isSupportedOutput (int) ; 
 int sws_setColorspaceDetails (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mp_sws_reinit(struct mp_sws_context *ctx)
{
    struct mp_image_params *src = &ctx->src;
    struct mp_image_params *dst = &ctx->dst;

    // Neutralize unsupported or ignored parameters.
    src->p_w = dst->p_w = 0;
    src->p_h = dst->p_h = 0;

    if (cache_valid(ctx))
        return 0;

    sws_freeContext(ctx->sws);
    ctx->sws = sws_alloc_context();
    if (!ctx->sws)
        return -1;

    mp_image_params_guess_csp(src); // sanitize colorspace/colorlevels
    mp_image_params_guess_csp(dst);

    struct mp_imgfmt_desc src_fmt = mp_imgfmt_get_desc(src->imgfmt);
    struct mp_imgfmt_desc dst_fmt = mp_imgfmt_get_desc(dst->imgfmt);
    if (!src_fmt.id || !dst_fmt.id)
        return -1;

    enum AVPixelFormat s_fmt = imgfmt2pixfmt(src->imgfmt);
    if (s_fmt == AV_PIX_FMT_NONE || sws_isSupportedInput(s_fmt) < 1) {
        MP_ERR(ctx, "Input image format %s not supported by libswscale.\n",
               mp_imgfmt_to_name(src->imgfmt));
        return -1;
    }

    enum AVPixelFormat d_fmt = imgfmt2pixfmt(dst->imgfmt);
    if (d_fmt == AV_PIX_FMT_NONE || sws_isSupportedOutput(d_fmt) < 1) {
        MP_ERR(ctx, "Output image format %s not supported by libswscale.\n",
               mp_imgfmt_to_name(dst->imgfmt));
        return -1;
    }

    int s_csp = mp_csp_to_sws_colorspace(src->color.space);
    int s_range = src->color.levels == MP_CSP_LEVELS_PC;

    int d_csp = mp_csp_to_sws_colorspace(dst->color.space);
    int d_range = dst->color.levels == MP_CSP_LEVELS_PC;

    // Work around libswscale bug #1852 (fixed in ffmpeg commit 8edf9b1fa):
    // setting range flags for RGB gives random bogus results.
    // Newer libswscale always ignores range flags for RGB.
    s_range = s_range && (src_fmt.flags & MP_IMGFLAG_YUV);
    d_range = d_range && (dst_fmt.flags & MP_IMGFLAG_YUV);

    av_opt_set_int(ctx->sws, "sws_flags", ctx->flags, 0);

    av_opt_set_int(ctx->sws, "srcw", src->w, 0);
    av_opt_set_int(ctx->sws, "srch", src->h, 0);
    av_opt_set_int(ctx->sws, "src_format", s_fmt, 0);

    av_opt_set_int(ctx->sws, "dstw", dst->w, 0);
    av_opt_set_int(ctx->sws, "dsth", dst->h, 0);
    av_opt_set_int(ctx->sws, "dst_format", d_fmt, 0);

    av_opt_set_double(ctx->sws, "param0", ctx->params[0], 0);
    av_opt_set_double(ctx->sws, "param1", ctx->params[1], 0);

#if LIBAVCODEC_VERSION_MICRO >= 100
    int cr_src = mp_chroma_location_to_av(src->chroma_location);
    int cr_dst = mp_chroma_location_to_av(dst->chroma_location);
    int cr_xpos, cr_ypos;
    if (avcodec_enum_to_chroma_pos(&cr_xpos, &cr_ypos, cr_src) >= 0) {
        av_opt_set_int(ctx->sws, "src_h_chr_pos", cr_xpos, 0);
        av_opt_set_int(ctx->sws, "src_v_chr_pos", cr_ypos, 0);
    }
    if (avcodec_enum_to_chroma_pos(&cr_xpos, &cr_ypos, cr_dst) >= 0) {
        av_opt_set_int(ctx->sws, "dst_h_chr_pos", cr_xpos, 0);
        av_opt_set_int(ctx->sws, "dst_v_chr_pos", cr_ypos, 0);
    }
#endif

    // This can fail even with normal operation, e.g. if a conversion path
    // simply does not support these settings.
    int r =
        sws_setColorspaceDetails(ctx->sws, sws_getCoefficients(s_csp), s_range,
                                 sws_getCoefficients(d_csp), d_range,
                                 ctx->brightness, ctx->contrast, ctx->saturation);
    ctx->supports_csp = r >= 0;

    if (sws_init_context(ctx->sws, ctx->src_filter, ctx->dst_filter) < 0)
        return -1;

    ctx->force_reload = false;
    *ctx->cached = *ctx;
    return 1;
}