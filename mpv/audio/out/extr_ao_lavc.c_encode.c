#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct priv {double aframecount; int aframesize; scalar_t__ lastpts; TYPE_4__* enc; int /*<<< orphan*/  worst_time_base; } ;
struct encode_lavc_context {double audio_pts_offset; int /*<<< orphan*/  lock; } ;
struct TYPE_8__ {int num; } ;
struct ao {double samplerate; int sstride; TYPE_1__ channels; int /*<<< orphan*/  format; struct encode_lavc_context* encode_lavc_ctx; struct priv* priv; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_11__ {TYPE_3__* encoder; } ;
struct TYPE_10__ {int /*<<< orphan*/  global_quality; int /*<<< orphan*/  time_base; } ;
struct TYPE_9__ {int nb_samples; int* linesize; scalar_t__ pts; int /*<<< orphan*/  quality; void** extended_data; int /*<<< orphan*/  format; } ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 size_t AV_NUM_DATA_POINTERS ; 
 int /*<<< orphan*/  MP_WARN (struct ao*,char*,int,int) ; 
 scalar_t__ af_fmt_is_planar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  af_to_avformat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* av_frame_alloc () ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int /*<<< orphan*/  av_inv_q (int /*<<< orphan*/ ) ; 
 double av_q2d (int /*<<< orphan*/ ) ; 
 scalar_t__ av_rescale_q (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encoder_encode (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ rint (double) ; 

__attribute__((used)) static void encode(struct ao *ao, double apts, void **data)
{
    struct priv *ac = ao->priv;
    struct encode_lavc_context *ectx = ao->encode_lavc_ctx;
    AVCodecContext *encoder = ac->enc->encoder;
    double realapts = ac->aframecount * (double) ac->aframesize /
                      ao->samplerate;

    ac->aframecount++;

    pthread_mutex_lock(&ectx->lock);
    if (data)
        ectx->audio_pts_offset = realapts - apts;
    pthread_mutex_unlock(&ectx->lock);

    if(data) {
        AVFrame *frame = av_frame_alloc();
        frame->format = af_to_avformat(ao->format);
        frame->nb_samples = ac->aframesize;

        size_t num_planes = af_fmt_is_planar(ao->format) ? ao->channels.num : 1;
        assert(num_planes <= AV_NUM_DATA_POINTERS);
        for (int n = 0; n < num_planes; n++)
            frame->extended_data[n] = data[n];

        frame->linesize[0] = frame->nb_samples * ao->sstride;

        frame->pts = rint(apts * av_q2d(av_inv_q(encoder->time_base)));

        int64_t frame_pts = av_rescale_q(frame->pts, encoder->time_base,
                                         ac->worst_time_base);
        if (ac->lastpts != AV_NOPTS_VALUE && frame_pts <= ac->lastpts) {
            // this indicates broken video
            // (video pts failing to increase fast enough to match audio)
            MP_WARN(ao, "audio frame pts went backwards (%d <- %d), autofixed\n",
                    (int)frame->pts, (int)ac->lastpts);
            frame_pts = ac->lastpts + 1;
            frame->pts = av_rescale_q(frame_pts, ac->worst_time_base,
                                      encoder->time_base);
        }
        ac->lastpts = frame_pts;

        frame->quality = encoder->global_quality;
        encoder_encode(ac->enc, frame);
        av_frame_free(&frame);
    } else {
        encoder_encode(ac->enc, NULL);
    }
}