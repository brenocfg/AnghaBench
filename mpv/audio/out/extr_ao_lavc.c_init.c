#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct priv {int sample_size; int pcmhack; int aframesize; int framecount; int shutdown; void* lastpts; void* savepts; TYPE_4__* enc; } ;
struct mp_chmap_sel {int /*<<< orphan*/  member_0; } ;
struct TYPE_17__ {scalar_t__ num; } ;
struct ao {int samplerate; int untimed; int period_size; TYPE_10__* encode_lavc_ctx; TYPE_6__ channels; int /*<<< orphan*/  format; int /*<<< orphan*/  log; struct priv* priv; } ;
struct TYPE_16__ {TYPE_2__* encoder; } ;
struct TYPE_15__ {int /*<<< orphan*/  supported_samplerates; } ;
struct TYPE_13__ {int num; int den; } ;
struct TYPE_14__ {int sample_rate; scalar_t__ channels; int bits_per_raw_sample; int frame_size; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  sample_fmt; int /*<<< orphan*/  channel_layout; TYPE_1__ time_base; TYPE_3__* codec; } ;
struct TYPE_12__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ AVCodecContext ;
typedef  TYPE_3__ AVCodec ;

/* Variables and functions */
 void* AV_NOPTS_VALUE ; 
 scalar_t__ AV_NUM_DATA_POINTERS ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_NONE ; 
 int MPMAX (int,int) ; 
 int /*<<< orphan*/  STREAM_AUDIO ; 
 int af_fmt_to_bytes (int /*<<< orphan*/ ) ; 
 int af_select_best_samplerate (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  af_to_avformat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ao_chmap_sel_adjust2 (struct ao*,struct mp_chmap_sel*,TYPE_6__*,int) ; 
 int av_get_bits_per_sample (int /*<<< orphan*/ ) ; 
 int ceil (double) ; 
 TYPE_4__* encoder_context_alloc (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encoder_init_codec_and_muxer (TYPE_4__*,int /*<<< orphan*/ ,struct ao*) ; 
 int /*<<< orphan*/  mp_chmap_reorder_to_lavc (TYPE_6__*) ; 
 int /*<<< orphan*/  mp_chmap_sel_add_any (struct mp_chmap_sel*) ; 
 int /*<<< orphan*/  mp_chmap_to_lavc (TYPE_6__*) ; 
 int /*<<< orphan*/  on_ready ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  select_format (struct ao*,TYPE_3__ const*) ; 
 int /*<<< orphan*/  talloc_steal (struct priv*,TYPE_4__*) ; 

__attribute__((used)) static int init(struct ao *ao)
{
    struct priv *ac = ao->priv;

    ac->enc = encoder_context_alloc(ao->encode_lavc_ctx, STREAM_AUDIO, ao->log);
    if (!ac->enc)
        return -1;
    talloc_steal(ac, ac->enc);

    AVCodecContext *encoder = ac->enc->encoder;
    const AVCodec *codec = encoder->codec;

    int samplerate = af_select_best_samplerate(ao->samplerate,
                                               codec->supported_samplerates);
    if (samplerate > 0)
        ao->samplerate = samplerate;

    encoder->time_base.num = 1;
    encoder->time_base.den = ao->samplerate;

    encoder->sample_rate = ao->samplerate;

    struct mp_chmap_sel sel = {0};
    mp_chmap_sel_add_any(&sel);
    if (!ao_chmap_sel_adjust2(ao, &sel, &ao->channels, false))
        goto fail;
    mp_chmap_reorder_to_lavc(&ao->channels);
    encoder->channels = ao->channels.num;
    encoder->channel_layout = mp_chmap_to_lavc(&ao->channels);

    encoder->sample_fmt = AV_SAMPLE_FMT_NONE;

    select_format(ao, codec);

    ac->sample_size = af_fmt_to_bytes(ao->format);
    encoder->sample_fmt = af_to_avformat(ao->format);
    encoder->bits_per_raw_sample = ac->sample_size * 8;

    if (!encoder_init_codec_and_muxer(ac->enc, on_ready, ao))
        goto fail;

    ac->pcmhack = 0;
    if (encoder->frame_size <= 1)
        ac->pcmhack = av_get_bits_per_sample(encoder->codec_id) / 8;

    if (ac->pcmhack) {
        ac->aframesize = 16384; // "enough"
    } else {
        ac->aframesize = encoder->frame_size;
    }

    // enough frames for at least 0.25 seconds
    ac->framecount = ceil(ao->samplerate * 0.25 / ac->aframesize);
    // but at least one!
    ac->framecount = MPMAX(ac->framecount, 1);

    ac->savepts = AV_NOPTS_VALUE;
    ac->lastpts = AV_NOPTS_VALUE;

    ao->untimed = true;

    ao->period_size = ac->aframesize * ac->framecount;

    if (ao->channels.num > AV_NUM_DATA_POINTERS)
        goto fail;

    return 0;

fail:
    pthread_mutex_unlock(&ao->encode_lavc_ctx->lock);
    ac->shutdown = true;
    return -1;
}