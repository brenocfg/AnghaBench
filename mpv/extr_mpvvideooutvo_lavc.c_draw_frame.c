#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct vo_frame {int num_frames; struct mp_image** frames; scalar_t__ repeat; scalar_t__ redraw; } ;
struct vo {int /*<<< orphan*/  osd; int /*<<< orphan*/  params; struct priv* priv; } ;
struct priv {scalar_t__ shutdown; struct encoder_context* enc; } ;
struct mp_osd_res {int dummy; } ;
struct mp_image {double pts; } ;
struct encoder_context {TYPE_1__* options; TYPE_3__* encoder; struct encode_lavc_context* encode_lavc_ctx; } ;
struct encode_lavc_context {double discontinuity_pts_offset; double next_in_pts; int /*<<< orphan*/  lock; } ;
struct TYPE_9__ {int /*<<< orphan*/  global_quality; int /*<<< orphan*/  time_base; } ;
struct TYPE_8__ {int /*<<< orphan*/  quality; scalar_t__ pict_type; int /*<<< orphan*/  pts; } ;
struct TYPE_7__ {int /*<<< orphan*/  rawts; } ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 double MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  MP_WARN (struct vo*,char*,double) ; 
 int /*<<< orphan*/  OSD_DRAW_SUB_ONLY ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int /*<<< orphan*/  av_inv_q (int /*<<< orphan*/ ) ; 
 double av_q2d (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encoder_encode (struct encoder_context*,TYPE_2__*) ; 
 scalar_t__ encoder_get_offset (struct encoder_context*) ; 
 int fabs (double) ; 
 TYPE_2__* mp_image_to_av_frame (struct mp_image*) ; 
 int /*<<< orphan*/  osd_draw_on_image (int /*<<< orphan*/ ,struct mp_osd_res,double,int /*<<< orphan*/ ,struct mp_image*) ; 
 struct mp_osd_res osd_res_from_image_params (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rint (double) ; 

__attribute__((used)) static void draw_frame(struct vo *vo, struct vo_frame *voframe)
{
    struct priv *vc = vo->priv;
    struct encoder_context *enc = vc->enc;
    struct encode_lavc_context *ectx = enc->encode_lavc_ctx;
    AVCodecContext *avc = enc->encoder;

    if (voframe->redraw || voframe->repeat || voframe->num_frames < 1)
        return;

    struct mp_image *mpi = voframe->frames[0];

    struct mp_osd_res dim = osd_res_from_image_params(vo->params);
    osd_draw_on_image(vo->osd, dim, mpi->pts, OSD_DRAW_SUB_ONLY, mpi);

    if (vc->shutdown)
        return;

    // Lock for shared timestamp fields.
    pthread_mutex_lock(&ectx->lock);

    double pts = mpi->pts;
    double outpts = pts;
    if (!enc->options->rawts) {
        // fix the discontinuity pts offset
        if (ectx->discontinuity_pts_offset == MP_NOPTS_VALUE) {
            ectx->discontinuity_pts_offset = ectx->next_in_pts - pts;
        } else if (fabs(pts + ectx->discontinuity_pts_offset -
                        ectx->next_in_pts) > 30)
        {
            MP_WARN(vo, "detected an unexpected discontinuity (pts jumped by "
                    "%f seconds)\n",
                    pts + ectx->discontinuity_pts_offset - ectx->next_in_pts);
            ectx->discontinuity_pts_offset = ectx->next_in_pts - pts;
        }

        outpts = pts + ectx->discontinuity_pts_offset;
    }

    outpts += encoder_get_offset(enc);

    if (!enc->options->rawts) {
        // calculate expected pts of next video frame
        double timeunit = av_q2d(avc->time_base);
        double expected_next_pts = pts + timeunit;
        // set next allowed output pts value
        double nextpts = expected_next_pts + ectx->discontinuity_pts_offset;
        if (nextpts > ectx->next_in_pts)
            ectx->next_in_pts = nextpts;
    }

    pthread_mutex_unlock(&ectx->lock);

    AVFrame *frame = mp_image_to_av_frame(mpi);
    if (!frame)
        abort();

    frame->pts = rint(outpts * av_q2d(av_inv_q(avc->time_base)));
    frame->pict_type = 0; // keep this at unknown/undefined
    frame->quality = avc->global_quality;
    encoder_encode(enc, frame);
    av_frame_free(&frame);
}