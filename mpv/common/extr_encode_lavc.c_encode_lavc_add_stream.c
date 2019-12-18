#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mux_stream {void (* on_ready ) (void*) ;void* on_ready_ctx; TYPE_1__* st; int /*<<< orphan*/  encoder_timebase; } ;
struct encoder_stream_info {TYPE_2__* codecpar; int /*<<< orphan*/  timebase; } ;
struct encode_priv {int failed; int /*<<< orphan*/  muxer; } ;
struct encode_lavc_context {int /*<<< orphan*/  lock; struct encode_priv* priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  sample_aspect_ratio; int /*<<< orphan*/  codec_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  codecpar; int /*<<< orphan*/  sample_aspect_ratio; int /*<<< orphan*/  time_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  MP_ERR (struct encode_priv*,char*) ; 
 int /*<<< orphan*/  MP_HANDLE_OOM (TYPE_1__*) ; 
 scalar_t__ avcodec_parameters_copy (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_1__* avformat_new_stream (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mux_stream* find_mux_stream (struct encode_lavc_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maybe_init_muxer (struct encode_lavc_context*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mux_stream *encode_lavc_add_stream(struct encode_lavc_context *ctx,
                                                 struct encoder_stream_info *info,
                                                 void (*on_ready)(void *ctx),
                                                 void *on_ready_ctx)
{
    struct encode_priv *p = ctx->priv;

    pthread_mutex_lock(&ctx->lock);

    struct mux_stream *dst = find_mux_stream(ctx, info->codecpar->codec_type);
    if (!dst) {
        MP_ERR(p, "Cannot add a stream at runtime.\n");
        p->failed = true;
        goto done;
    }
    if (dst->st) {
        // Possibly via --gapless-audio, or explicitly recreating AO/VO.
        MP_ERR(p, "Encoder was reinitialized; this is not allowed.\n");
        p->failed = true;
        dst = NULL;
        goto done;
    }

    dst->st = avformat_new_stream(p->muxer, NULL);
    MP_HANDLE_OOM(dst->st);

    dst->encoder_timebase = info->timebase;
    dst->st->time_base = info->timebase; // lavf will change this on muxer init
    // Some muxers (e.g. Matroska one) expect the sample_aspect_ratio to be
    // set on the AVStream.
    if (info->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
        dst->st->sample_aspect_ratio = info->codecpar->sample_aspect_ratio;
    
    if (avcodec_parameters_copy(dst->st->codecpar, info->codecpar) < 0)
        MP_HANDLE_OOM(0);

    dst->on_ready = on_ready;
    dst->on_ready_ctx = on_ready_ctx;

    maybe_init_muxer(ctx);

done:
    pthread_mutex_unlock(&ctx->lock);

    return dst;
}