#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct track {TYPE_3__* demuxer; struct dec_sub* d_sub; } ;
struct mp_image_params {scalar_t__ imgfmt; } ;
struct dec_sub {int dummy; } ;
struct MPContext {scalar_t__ video_status; scalar_t__ video_out; int /*<<< orphan*/  osd; struct track*** current_track; TYPE_2__* vo_chain; } ;
struct TYPE_6__ {scalar_t__ fully_read; } ;
struct TYPE_5__ {TYPE_1__* filter; } ;
struct TYPE_4__ {struct mp_image_params input_params; } ;

/* Variables and functions */
 double MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  SD_CTRL_SET_VIDEO_PARAMS ; 
 scalar_t__ STATUS_EOF ; 
 size_t STREAM_SUB ; 
 int /*<<< orphan*/  demux_seek (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_set_timeout (struct MPContext*,double) ; 
 double osd_get_force_video_pts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osd_query_and_reset_want_redraw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osd_set_force_video_pts (int /*<<< orphan*/ ,double) ; 
 scalar_t__ sub_can_preload (struct dec_sub*) ; 
 int /*<<< orphan*/  sub_control (struct dec_sub*,int /*<<< orphan*/ ,struct mp_image_params*) ; 
 int /*<<< orphan*/  sub_get_text (struct dec_sub*,double) ; 
 int /*<<< orphan*/  sub_preload (struct dec_sub*) ; 
 int /*<<< orphan*/  sub_read_packets (struct dec_sub*,double) ; 
 int /*<<< orphan*/  term_osd_set_subs (struct MPContext*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vo_redraw (scalar_t__) ; 

__attribute__((used)) static bool update_subtitle(struct MPContext *mpctx, double video_pts,
                            struct track *track)
{
    struct dec_sub *dec_sub = track ? track->d_sub : NULL;

    if (!dec_sub || video_pts == MP_NOPTS_VALUE)
        return true;

    if (mpctx->vo_chain) {
        struct mp_image_params params = mpctx->vo_chain->filter->input_params;
        if (params.imgfmt)
            sub_control(dec_sub, SD_CTRL_SET_VIDEO_PARAMS, &params);
    }

    if (track->demuxer->fully_read && sub_can_preload(dec_sub)) {
        // Assume fully_read implies no interleaved audio/video streams.
        // (Reading packets will change the demuxer position.)
        demux_seek(track->demuxer, 0, 0);
        sub_preload(dec_sub);
    }

    if (!sub_read_packets(dec_sub, video_pts))
        return false;

    // Handle displaying subtitles on terminal; never done for secondary subs
    if (mpctx->current_track[0][STREAM_SUB] == track && !mpctx->video_out)
        term_osd_set_subs(mpctx, sub_get_text(dec_sub, video_pts));

    // Handle displaying subtitles on VO with no video being played. This is
    // quite different, because normally subtitles are redrawn on new video
    // frames, using the video frames' timestamps.
    if (mpctx->video_out && mpctx->video_status == STATUS_EOF) {
        if (osd_get_force_video_pts(mpctx->osd) != video_pts) {
            osd_set_force_video_pts(mpctx->osd, video_pts);
            osd_query_and_reset_want_redraw(mpctx->osd);
            vo_redraw(mpctx->video_out);
            // Force an arbitrary minimum FPS
            mp_set_timeout(mpctx, 0.1);
        }
    }

    return true;
}