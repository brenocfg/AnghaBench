#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct priv {double end; double start; scalar_t__ new_segment; } ;
struct mp_image {double pts; } ;
struct mp_frame {scalar_t__ type; struct mp_image* data; } ;
struct mp_aframe {double pts; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct priv*,char*) ; 
 scalar_t__ MP_FRAME_AUDIO ; 
 scalar_t__ MP_FRAME_EOF ; 
 scalar_t__ MP_FRAME_VIDEO ; 
 double MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  mp_aframe_clip_timestamps (struct mp_image*,double,double) ; 
 double mp_aframe_get_pts (struct mp_image*) ; 
 scalar_t__ mp_aframe_get_size (struct mp_image*) ; 
 int /*<<< orphan*/  mp_frame_unref (struct mp_frame*) ; 
 int /*<<< orphan*/  process_audio_frame (struct priv*,struct mp_image*) ; 
 int /*<<< orphan*/  process_video_frame (struct priv*,struct mp_image*) ; 

__attribute__((used)) static bool process_decoded_frame(struct priv *p, struct mp_frame *frame)
{
    if (frame->type == MP_FRAME_EOF) {
        // if we were just draining current segment, don't propagate EOF
        if (p->new_segment)
            mp_frame_unref(frame);
        return true;
    }

    bool segment_ended = false;

    if (frame->type == MP_FRAME_VIDEO) {
        struct mp_image *mpi = frame->data;

        process_video_frame(p, mpi);

        if (mpi->pts != MP_NOPTS_VALUE) {
            double vpts = mpi->pts;
            segment_ended = p->end != MP_NOPTS_VALUE && vpts >= p->end;
            if ((p->start != MP_NOPTS_VALUE && vpts < p->start) || segment_ended)
                mp_frame_unref(frame);
        }
    } else if (frame->type == MP_FRAME_AUDIO) {
        struct mp_aframe *aframe = frame->data;

        process_audio_frame(p, aframe);

        mp_aframe_clip_timestamps(aframe, p->start, p->end);
        double pts = mp_aframe_get_pts(aframe);
        if (pts != MP_NOPTS_VALUE && p->start != MP_NOPTS_VALUE)
            segment_ended = pts >= p->end;
        if (mp_aframe_get_size(aframe) == 0)
            mp_frame_unref(frame);
    } else {
        MP_ERR(p, "unknown frame type from decoder\n");
    }

    return segment_ended;
}