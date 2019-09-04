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
struct mp_decoder {int /*<<< orphan*/  control; struct mp_filter* f; } ;
struct TYPE_6__ {struct mp_decoder public; int /*<<< orphan*/  avctx; int /*<<< orphan*/  vo; int /*<<< orphan*/  hwdec_devs; int /*<<< orphan*/  dr_lock; void* dr_pool; void* hwdec_swpool; int /*<<< orphan*/  decoder; struct mp_codec_params* codec; TYPE_4__* opts_cache; int /*<<< orphan*/  opts; int /*<<< orphan*/  log; } ;
typedef  TYPE_1__ vd_ffmpeg_ctx ;
struct mp_stream_info {int /*<<< orphan*/  dr_vo; int /*<<< orphan*/  hwdec_devs; } ;
struct mp_filter {int /*<<< orphan*/  global; int /*<<< orphan*/  log; TYPE_1__* priv; } ;
struct mp_codec_params {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_PIN_IN ; 
 int /*<<< orphan*/  MP_PIN_OUT ; 
 int /*<<< orphan*/  control ; 
 TYPE_4__* m_config_cache_alloc (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_filter_add_pin (struct mp_filter*,int /*<<< orphan*/ ,char*) ; 
 struct mp_filter* mp_filter_create (struct mp_filter*,int /*<<< orphan*/ *) ; 
 struct mp_stream_info* mp_filter_find_stream_info (struct mp_filter*) ; 
 void* mp_image_pool_new (TYPE_1__*) ; 
 int /*<<< orphan*/  mp_log_new (struct mp_filter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit (struct mp_filter*) ; 
 int /*<<< orphan*/  talloc_free (struct mp_filter*) ; 
 int /*<<< orphan*/  talloc_strdup (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  vd_lavc_conf ; 
 int /*<<< orphan*/  vd_lavc_filter ; 

__attribute__((used)) static struct mp_decoder *create(struct mp_filter *parent,
                                 struct mp_codec_params *codec,
                                 const char *decoder)
{
    struct mp_filter *vd = mp_filter_create(parent, &vd_lavc_filter);
    if (!vd)
        return NULL;

    mp_filter_add_pin(vd, MP_PIN_IN, "in");
    mp_filter_add_pin(vd, MP_PIN_OUT, "out");

    vd->log = mp_log_new(vd, parent->log, NULL);

    vd_ffmpeg_ctx *ctx = vd->priv;
    ctx->log = vd->log;
    ctx->opts_cache = m_config_cache_alloc(ctx, vd->global, &vd_lavc_conf);
    ctx->opts = ctx->opts_cache->opts;
    ctx->codec = codec;
    ctx->decoder = talloc_strdup(ctx, decoder);
    ctx->hwdec_swpool = mp_image_pool_new(ctx);
    ctx->dr_pool = mp_image_pool_new(ctx);

    ctx->public.f = vd;
    ctx->public.control = control;

    pthread_mutex_init(&ctx->dr_lock, NULL);

    // hwdec/DR
    struct mp_stream_info *info = mp_filter_find_stream_info(vd);
    if (info) {
        ctx->hwdec_devs = info->hwdec_devs;
        ctx->vo = info->dr_vo;
    }

    reinit(vd);

    if (!ctx->avctx) {
        talloc_free(vd);
        return NULL;
    }
    return &ctx->public;
}