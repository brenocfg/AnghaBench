#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct spdifContext {scalar_t__ codec_id; } ;
struct mp_filter {struct spdifContext* priv; } ;
struct TYPE_17__ {int profile; int sample_rate; } ;
struct TYPE_16__ {int /*<<< orphan*/  flags; } ;
struct TYPE_15__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ AVPacket ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_2__ AVCodecParserContext ;
typedef  TYPE_3__ AVCodecContext ;
typedef  int /*<<< orphan*/  AVCodec ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_DTS ; 
 int FF_PROFILE_UNKNOWN ; 
 int /*<<< orphan*/  MP_WARN (struct mp_filter*,char*) ; 
 int /*<<< orphan*/  PARSER_FLAG_COMPLETE_FRAMES ; 
 int /*<<< orphan*/ * av_frame_alloc () ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_parser_close (TYPE_2__*) ; 
 TYPE_2__* av_parser_init (scalar_t__) ; 
 int /*<<< orphan*/  av_parser_parse2 (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* avcodec_alloc_context3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * avcodec_find_decoder (scalar_t__) ; 
 int /*<<< orphan*/  avcodec_free_context (TYPE_3__**) ; 
 scalar_t__ avcodec_open2 (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ avcodec_receive_frame (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ avcodec_send_packet (TYPE_3__*,TYPE_1__*) ; 

__attribute__((used)) static void determine_codec_params(struct mp_filter *da, AVPacket *pkt,
                                   int *out_profile, int *out_rate)
{
    struct spdifContext *spdif_ctx = da->priv;
    int profile = FF_PROFILE_UNKNOWN;
    AVCodecContext *ctx = NULL;
    AVFrame *frame = NULL;

    AVCodecParserContext *parser = av_parser_init(spdif_ctx->codec_id);
    if (parser) {
        // Don't make it wait for the next frame.
        parser->flags |= PARSER_FLAG_COMPLETE_FRAMES;

        ctx = avcodec_alloc_context3(NULL);
        if (!ctx) {
            av_parser_close(parser);
            goto done;
        }

        uint8_t *d = NULL;
        int s = 0;
        av_parser_parse2(parser, ctx, &d, &s, pkt->data, pkt->size, 0, 0, 0);
        *out_profile = profile = ctx->profile;
        *out_rate = ctx->sample_rate;

        avcodec_free_context(&ctx);
        av_parser_close(parser);
    }

    if (profile != FF_PROFILE_UNKNOWN || spdif_ctx->codec_id != AV_CODEC_ID_DTS)
        return;

    AVCodec *codec = avcodec_find_decoder(spdif_ctx->codec_id);
    if (!codec)
        goto done;

    frame = av_frame_alloc();
    if (!frame)
        goto done;

    ctx = avcodec_alloc_context3(codec);
    if (!ctx)
        goto done;

    if (avcodec_open2(ctx, codec, NULL) < 0)
        goto done;

    if (avcodec_send_packet(ctx, pkt) < 0)
        goto done;
    if (avcodec_receive_frame(ctx, frame) < 0)
        goto done;

    *out_profile = profile = ctx->profile;
    *out_rate = ctx->sample_rate;

done:
    av_frame_free(&frame);
    avcodec_free_context(&ctx);

    if (profile == FF_PROFILE_UNKNOWN)
        MP_WARN(da, "Failed to parse codec profile.\n");
}