#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct track {scalar_t__ d_sub; TYPE_1__* stream; int /*<<< orphan*/  demuxer; } ;
struct mp_codec_params {int fps; } ;
struct MPContext {struct track*** current_track; int /*<<< orphan*/  global; } ;
struct TYPE_2__ {struct mp_codec_params* codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  SD_CTRL_SET_VIDEO_DEF_FPS ; 
 size_t STREAM_VIDEO ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  get_all_attachments (struct MPContext*) ; 
 int /*<<< orphan*/  sub_control (scalar_t__,int /*<<< orphan*/ ,double*) ; 
 scalar_t__ sub_create (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool init_subdec(struct MPContext *mpctx, struct track *track)
{
    assert(!track->d_sub);

    if (!track->demuxer || !track->stream)
        return false;

    track->d_sub = sub_create(mpctx->global, track->stream,
                              get_all_attachments(mpctx));
    if (!track->d_sub)
        return false;

    struct track *vtrack = mpctx->current_track[0][STREAM_VIDEO];
    struct mp_codec_params *v_c =
        vtrack && vtrack->stream ? vtrack->stream->codec : NULL;
    double fps = v_c ? v_c->fps : 25;
    sub_control(track->d_sub, SD_CTRL_SET_VIDEO_DEF_FPS, &fps);

    return true;
}