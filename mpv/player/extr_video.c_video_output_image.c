#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vo_chain {scalar_t__ is_coverart; TYPE_2__* filter; } ;
struct mp_image {double pts; } ;
struct mp_frame {scalar_t__ type; struct mp_image* data; } ;
struct MPContext {scalar_t__ video_status; double play_dir; scalar_t__ max_frames; double hrseek_pts; int hrseek_backstep; double playback_pts; struct mp_image* saved_frame; scalar_t__ hrseek_lastframe; int /*<<< orphan*/  video_out; scalar_t__ hrseek_active; struct vo_chain* vo_chain; } ;
struct TYPE_4__ {TYPE_1__* f; scalar_t__ got_output_eof; } ;
struct TYPE_3__ {int /*<<< orphan*/ * pins; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct MPContext*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ MP_FRAME_EOF ; 
 scalar_t__ MP_FRAME_NONE ; 
 scalar_t__ MP_FRAME_VIDEO ; 
 double MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  MP_WARN (struct MPContext*,char*) ; 
 scalar_t__ STATUS_SYNCING ; 
 int VD_EOF ; 
 int VD_ERROR ; 
 int VD_NEW_FRAME ; 
 int VD_PROGRESS ; 
 int VD_WAIT ; 
 int /*<<< orphan*/  add_new_frame (struct MPContext*,struct mp_image*) ; 
 double get_play_end_pts (struct MPContext*) ; 
 scalar_t__ have_new_frame (struct MPContext*,int) ; 
 int /*<<< orphan*/  mp_frame_type_str (scalar_t__) ; 
 int /*<<< orphan*/  mp_frame_unref (struct mp_frame*) ; 
 int /*<<< orphan*/  mp_image_setrefp (struct mp_image**,struct mp_image*) ; 
 struct mp_frame mp_pin_out_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_pin_out_unread (int /*<<< orphan*/ ,struct mp_frame) ; 
 scalar_t__ needs_new_frame (struct MPContext*) ; 
 int /*<<< orphan*/  talloc_free (struct mp_image*) ; 
 scalar_t__ vo_has_frame (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int video_output_image(struct MPContext *mpctx)
{
    struct vo_chain *vo_c = mpctx->vo_chain;
    bool hrseek = mpctx->hrseek_active && mpctx->video_status == STATUS_SYNCING;

    if (vo_c->is_coverart) {
        if (vo_has_frame(mpctx->video_out))
            return VD_EOF;
        hrseek = false;
    }

    if (have_new_frame(mpctx, false))
        return VD_NEW_FRAME;

    // Get a new frame if we need one.
    int r = VD_PROGRESS;
    if (needs_new_frame(mpctx)) {
        // Filter a new frame.
        struct mp_image *img = NULL;
        struct mp_frame frame = mp_pin_out_read(vo_c->filter->f->pins[1]);
        if (frame.type == MP_FRAME_NONE) {
            r = vo_c->filter->got_output_eof ? VD_EOF : VD_WAIT;
        } else if (frame.type == MP_FRAME_EOF) {
            r = VD_EOF;
        } else if (frame.type == MP_FRAME_VIDEO) {
            img = frame.data;
        } else {
            MP_ERR(mpctx, "unexpected frame type %s\n",
                   mp_frame_type_str(frame.type));
            mp_frame_unref(&frame);
            return VD_ERROR;
        }
        if (img) {
            double endpts = get_play_end_pts(mpctx);
            if (endpts != MP_NOPTS_VALUE)
                endpts *= mpctx->play_dir;
            if ((endpts != MP_NOPTS_VALUE && img->pts >= endpts) ||
                mpctx->max_frames == 0)
            {
                mp_pin_out_unread(vo_c->filter->f->pins[1], frame);
                img = NULL;
                r = VD_EOF;
            } else if (hrseek && mpctx->hrseek_lastframe) {
                mp_image_setrefp(&mpctx->saved_frame, img);
            } else if (hrseek && img->pts < mpctx->hrseek_pts - .005) {
                /* just skip - but save if backstep active */
                if (mpctx->hrseek_backstep)
                    mp_image_setrefp(&mpctx->saved_frame, img);
            } else if (mpctx->video_status == STATUS_SYNCING &&
                       mpctx->playback_pts != MP_NOPTS_VALUE &&
                       img->pts < mpctx->playback_pts && !vo_c->is_coverart)
            {
                /* skip after stream-switching */
            } else {
                if (hrseek && mpctx->hrseek_backstep) {
                    if (mpctx->saved_frame) {
                        add_new_frame(mpctx, mpctx->saved_frame);
                        mpctx->saved_frame = NULL;
                    } else {
                        MP_WARN(mpctx, "Backstep failed.\n");
                    }
                    mpctx->hrseek_backstep = false;
                }
                add_new_frame(mpctx, img);
                img = NULL;
            }
            talloc_free(img);
        }
    }

    // Last-frame seek
    if (r <= 0 && hrseek && mpctx->hrseek_lastframe && mpctx->saved_frame) {
        add_new_frame(mpctx, mpctx->saved_frame);
        mpctx->saved_frame = NULL;
        r = VD_PROGRESS;
    }

    return have_new_frame(mpctx, r <= 0) ? VD_NEW_FRAME : r;
}