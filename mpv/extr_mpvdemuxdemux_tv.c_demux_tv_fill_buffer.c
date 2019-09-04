#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_2__* tv_param; int /*<<< orphan*/  priv; TYPE_1__* functions; } ;
typedef  TYPE_3__ tvi_handle_t ;
struct sh_stream {scalar_t__ type; } ;
struct TYPE_15__ {scalar_t__ priv; } ;
typedef  TYPE_4__ demuxer_t ;
struct TYPE_16__ {int keyframe; int /*<<< orphan*/  buffer; int /*<<< orphan*/  pts; } ;
typedef  TYPE_5__ demux_packet_t ;
struct TYPE_13__ {scalar_t__ scan; scalar_t__ audio; } ;
struct TYPE_12__ {scalar_t__ (* control ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;unsigned int (* get_audio_framesize ) (int /*<<< orphan*/ ) ;unsigned int (* get_video_framesize ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* grab_video_frame ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ;int /*<<< orphan*/  (* grab_audio_frame ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ;} ;

/* Variables and functions */
 scalar_t__ STREAM_AUDIO ; 
 scalar_t__ STREAM_VIDEO ; 
 int /*<<< orphan*/  TVI_CONTROL_IS_AUDIO ; 
 int /*<<< orphan*/  TVI_CONTROL_IS_VIDEO ; 
 scalar_t__ TVI_CONTROL_TRUE ; 
 int /*<<< orphan*/  demux_add_packet (struct sh_stream*,TYPE_5__*) ; 
 int demux_get_num_stream (TYPE_4__*) ; 
 struct sh_stream* demux_get_stream (TYPE_4__*,int) ; 
 int /*<<< orphan*/  demux_has_packet (struct sh_stream*) ; 
 scalar_t__ demux_stream_is_selected (struct sh_stream*) ; 
 TYPE_5__* new_demux_packet (unsigned int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int stub5 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  tv_scan (TYPE_3__*) ; 

__attribute__((used)) static int demux_tv_fill_buffer(demuxer_t *demux)
{
    tvi_handle_t *tvh=(tvi_handle_t*)(demux->priv);
    demux_packet_t* dp;
    unsigned int len=0;
    struct sh_stream *want_audio = NULL, *want_video = NULL;

    int num_streams = demux_get_num_stream(demux);
    for (int n = 0; n < num_streams; n++) {
        struct sh_stream *sh = demux_get_stream(demux, n);
        if (!demux_has_packet(sh) && demux_stream_is_selected(sh)) {
            if (sh->type == STREAM_AUDIO)
                want_audio = sh;
            if (sh->type == STREAM_VIDEO)
                want_video = sh;
        }
    }

    /* ================== ADD AUDIO PACKET =================== */

    if (want_audio && tvh->tv_param->audio &&
        tvh->functions->control(tvh->priv,
                                TVI_CONTROL_IS_AUDIO, 0) == TVI_CONTROL_TRUE)
    {
        len = tvh->functions->get_audio_framesize(tvh->priv);

        dp=new_demux_packet(len);
        if (dp) {
            dp->keyframe = true;
            dp->pts=tvh->functions->grab_audio_frame(tvh->priv, dp->buffer,len);
            demux_add_packet(want_audio, dp);
        }
    }

    /* ================== ADD VIDEO PACKET =================== */

    if (want_video && tvh->functions->control(tvh->priv,
                            TVI_CONTROL_IS_VIDEO, 0) == TVI_CONTROL_TRUE)
    {
        len = tvh->functions->get_video_framesize(tvh->priv);
        dp=new_demux_packet(len);
        if (dp) {
            dp->keyframe = true;
            dp->pts=tvh->functions->grab_video_frame(tvh->priv, dp->buffer, len);
            demux_add_packet(want_video, dp);
        }
    }

    if (tvh->tv_param->scan) tv_scan(tvh);
    return 1;
}