#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int fps; } ;
struct priv {double codec_pts; scalar_t__ num_codec_pts_problems; double codec_dts; scalar_t__ num_codec_dts_problems; int has_broken_packet_pts; int has_broken_decoded_pts; double first_packet_pdts; double pts; double start_pts; int /*<<< orphan*/  header; TYPE_3__ public; TYPE_2__* decoder; TYPE_1__* codec; int /*<<< orphan*/  fixed_format; int /*<<< orphan*/  last_format; TYPE_4__* opt_cache; } ;
struct mp_image {double pts; double dts; int nominal_fps; int /*<<< orphan*/  a53_cc; int /*<<< orphan*/  params; } ;
struct demux_packet {int pts; double dts; } ;
struct MPOpts {scalar_t__ correct_pts; } ;
struct TYPE_8__ {struct MPOpts* opts; } ;
struct TYPE_6__ {int /*<<< orphan*/  f; int /*<<< orphan*/  (* control ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_5__ {scalar_t__ avi_dts; } ;

/* Variables and functions */
 int MPMAX (int,int /*<<< orphan*/ ) ; 
 double MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  MP_WARN (struct priv*,char*,...) ; 
 int /*<<< orphan*/  VDCTRL_GET_BFRAMES ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  demuxer_feed_caption (int /*<<< orphan*/ ,struct demux_packet*) ; 
 int /*<<< orphan*/  fix_image_params (struct priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_config_cache_update (TYPE_4__*) ; 
 int /*<<< orphan*/  mp_image_params_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct demux_packet* new_demux_packet_from_buf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void process_video_frame(struct priv *p, struct mp_image *mpi)
{
    struct MPOpts *opts = p->opt_cache->opts;
    m_config_cache_update(p->opt_cache);

    // Note: the PTS is reordered, but the DTS is not. Both should be monotonic.
    double pts = mpi->pts;
    double dts = mpi->dts;

    if (pts != MP_NOPTS_VALUE) {
        if (pts < p->codec_pts)
            p->num_codec_pts_problems++;
        p->codec_pts = mpi->pts;
    }

    if (dts != MP_NOPTS_VALUE) {
        if (dts <= p->codec_dts)
            p->num_codec_dts_problems++;
        p->codec_dts = mpi->dts;
    }

    if (p->has_broken_packet_pts < 0)
        p->has_broken_packet_pts++;
    if (p->num_codec_pts_problems)
        p->has_broken_packet_pts = 1;

    // If PTS is unset, or non-monotonic, fall back to DTS.
    if ((p->num_codec_pts_problems > p->num_codec_dts_problems ||
         pts == MP_NOPTS_VALUE) && dts != MP_NOPTS_VALUE)
        pts = dts;

    if (!opts->correct_pts || pts == MP_NOPTS_VALUE) {
        double fps = p->public.fps > 0 ? p->public.fps : 25;

        if (opts->correct_pts) {
            if (p->has_broken_decoded_pts <= 1) {
                MP_WARN(p, "No video PTS! Making something up. Using "
                        "%f FPS.\n", fps);
                if (p->has_broken_decoded_pts == 1)
                    MP_WARN(p, "Ignoring further missing PTS warnings.\n");
                p->has_broken_decoded_pts++;
            }
        }

        double frame_time = 1.0f / fps;
        double base = p->first_packet_pdts;
        pts = p->pts;
        if (pts == MP_NOPTS_VALUE) {
            pts = base == MP_NOPTS_VALUE ? 0 : base;
        } else {
            pts += frame_time;
        }
    }

    if (!mp_image_params_equal(&p->last_format, &mpi->params))
        fix_image_params(p, &mpi->params);

    mpi->params = p->fixed_format;
    mpi->nominal_fps = p->public.fps;

    mpi->pts = pts;
    p->pts = pts;

    // Compensate for incorrectly using mpeg-style DTS for avi timestamps.
    if (p->decoder && p->decoder->control && p->codec->avi_dts &&
        opts->correct_pts && mpi->pts != MP_NOPTS_VALUE && p->public.fps > 0)
    {
        int delay = -1;
        p->decoder->control(p->decoder->f, VDCTRL_GET_BFRAMES, &delay);
        mpi->pts -= MPMAX(delay, 0) / p->public.fps;
    }

    struct demux_packet *ccpkt = new_demux_packet_from_buf(mpi->a53_cc);
    if (ccpkt) {
        av_buffer_unref(&mpi->a53_cc);
        ccpkt->pts = mpi->pts;
        ccpkt->dts = mpi->dts;
        demuxer_feed_caption(p->header, ccpkt);
    }

    if (mpi->pts == MP_NOPTS_VALUE || mpi->pts >= p->start_pts)
        p->start_pts = MP_NOPTS_VALUE;
}