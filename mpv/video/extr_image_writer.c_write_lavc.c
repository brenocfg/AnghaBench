#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct image_writer_ctx {TYPE_1__* opts; } ;
struct AVCodec {scalar_t__ id; } ;
struct TYPE_22__ {scalar_t__ levels; int /*<<< orphan*/  gamma; int /*<<< orphan*/  primaries; } ;
struct TYPE_23__ {TYPE_2__ color; } ;
struct TYPE_24__ {TYPE_3__ params; int /*<<< orphan*/ * stride; int /*<<< orphan*/ * planes; int /*<<< orphan*/  imgfmt; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
typedef  TYPE_4__ mp_image_t ;
struct TYPE_27__ {scalar_t__ pix_fmt; int /*<<< orphan*/  color_range; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  compression_level; int /*<<< orphan*/  time_base; } ;
struct TYPE_26__ {scalar_t__ format; int /*<<< orphan*/  color_trc; int /*<<< orphan*/  color_primaries; int /*<<< orphan*/  color_range; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
struct TYPE_25__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; int /*<<< orphan*/  member_0; } ;
struct TYPE_21__ {scalar_t__ format; scalar_t__ tag_csp; int /*<<< orphan*/  webp_quality; int /*<<< orphan*/  webp_lossless; int /*<<< orphan*/  webp_compression; int /*<<< orphan*/  png_filter; int /*<<< orphan*/  png_compression; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_5__ AVPacket ;
typedef  TYPE_6__ AVFrame ;
typedef  TYPE_7__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_MJPEG ; 
 scalar_t__ AV_CODEC_ID_PNG ; 
 scalar_t__ AV_CODEC_ID_WEBP ; 
 int /*<<< orphan*/  AV_OPT_SEARCH_CHILDREN ; 
 scalar_t__ AV_PIX_FMT_NONE ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 scalar_t__ MP_CSP_LEVELS_PC ; 
 int /*<<< orphan*/  MP_ERR (struct image_writer_ctx*,char*,...) ; 
 TYPE_6__* av_frame_alloc () ; 
 int /*<<< orphan*/  av_frame_free (TYPE_6__**) ; 
 int /*<<< orphan*/  av_init_packet (TYPE_5__*) ; 
 int /*<<< orphan*/  av_opt_set_int (TYPE_7__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_5__*) ; 
 TYPE_7__* avcodec_alloc_context3 (struct AVCodec*) ; 
 struct AVCodec* avcodec_find_encoder (scalar_t__) ; 
 struct AVCodec* avcodec_find_encoder_by_name (char*) ; 
 int /*<<< orphan*/  avcodec_free_context (TYPE_7__**) ; 
 scalar_t__ avcodec_open2 (TYPE_7__*,struct AVCodec*,int /*<<< orphan*/ *) ; 
 int avcodec_receive_packet (TYPE_7__*,TYPE_5__*) ; 
 int avcodec_send_frame (TYPE_7__*,TYPE_6__*) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ imgfmt2pixfmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_csp_levels_to_avcol_range (scalar_t__) ; 
 int /*<<< orphan*/  mp_csp_prim_to_avcol_pri (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_csp_trc_to_avcol_trc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_imgfmt_to_name (int /*<<< orphan*/ ) ; 
 scalar_t__ replace_j_format (scalar_t__) ; 

__attribute__((used)) static bool write_lavc(struct image_writer_ctx *ctx, mp_image_t *image, FILE *fp)
{
    bool success = 0;
    AVFrame *pic = NULL;
    AVPacket pkt = {0};
    int got_output = 0;

    av_init_packet(&pkt);

    struct AVCodec *codec;
    if (ctx->opts->format == AV_CODEC_ID_WEBP) {
        codec = avcodec_find_encoder_by_name("libwebp"); // non-animated encoder
    } else {
        codec = avcodec_find_encoder(ctx->opts->format);
    }

    AVCodecContext *avctx = NULL;
    if (!codec)
        goto print_open_fail;
    avctx = avcodec_alloc_context3(codec);
    if (!avctx)
        goto print_open_fail;

    avctx->time_base = AV_TIME_BASE_Q;
    avctx->width = image->w;
    avctx->height = image->h;
    avctx->color_range = mp_csp_levels_to_avcol_range(image->params.color.levels);
    avctx->pix_fmt = imgfmt2pixfmt(image->imgfmt);
    if (codec->id == AV_CODEC_ID_MJPEG) {
        // Annoying deprecated garbage for the jpg encoder.
        if (image->params.color.levels == MP_CSP_LEVELS_PC)
            avctx->pix_fmt = replace_j_format(avctx->pix_fmt);
    }
    if (avctx->pix_fmt == AV_PIX_FMT_NONE) {
        MP_ERR(ctx, "Image format %s not supported by lavc.\n",
               mp_imgfmt_to_name(image->imgfmt));
        goto error_exit;
    }
    if (codec->id == AV_CODEC_ID_PNG) {
        avctx->compression_level = ctx->opts->png_compression;
        av_opt_set_int(avctx, "pred", ctx->opts->png_filter,
                       AV_OPT_SEARCH_CHILDREN);
    } else if (codec->id == AV_CODEC_ID_WEBP) {
        avctx->compression_level = ctx->opts->webp_compression;
        av_opt_set_int(avctx, "lossless", ctx->opts->webp_lossless,
                       AV_OPT_SEARCH_CHILDREN);
        av_opt_set_int(avctx, "quality", ctx->opts->webp_quality,
                       AV_OPT_SEARCH_CHILDREN);
    }

    if (avcodec_open2(avctx, codec, NULL) < 0) {
     print_open_fail:
        MP_ERR(ctx, "Could not open libavcodec encoder for saving images\n");
        goto error_exit;
    }

    pic = av_frame_alloc();
    if (!pic)
        goto error_exit;
    for (int n = 0; n < 4; n++) {
        pic->data[n] = image->planes[n];
        pic->linesize[n] = image->stride[n];
    }
    pic->format = avctx->pix_fmt;
    pic->width = avctx->width;
    pic->height = avctx->height;
    pic->color_range = avctx->color_range;
    if (ctx->opts->tag_csp) {
        pic->color_primaries = mp_csp_prim_to_avcol_pri(image->params.color.primaries);
        pic->color_trc = mp_csp_trc_to_avcol_trc(image->params.color.gamma);
    }

    int ret = avcodec_send_frame(avctx, pic);
    if (ret < 0)
        goto error_exit;
    ret = avcodec_send_frame(avctx, NULL); // send EOF
    if (ret < 0)
        goto error_exit;
    ret = avcodec_receive_packet(avctx, &pkt);
    if (ret < 0)
        goto error_exit;
    got_output = 1;

    fwrite(pkt.data, pkt.size, 1, fp);

    success = !!got_output;
error_exit:
    avcodec_free_context(&avctx);
    av_frame_free(&pic);
    av_packet_unref(&pkt);
    return success;
}