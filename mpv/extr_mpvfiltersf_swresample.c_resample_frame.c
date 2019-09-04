#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mp_aframe {int dummy; } ;
struct AVAudioResampleContext {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  nb_samples; int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * extended_data; } ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  MPMIN (int /*<<< orphan*/ ,int) ; 
 int avresample_convert (struct AVAudioResampleContext*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* mp_aframe_get_raw_avframe (struct mp_aframe*) ; 

__attribute__((used)) static int resample_frame(struct AVAudioResampleContext *r,
                          struct mp_aframe *out, struct mp_aframe *in,
                          int consume_in)
{
    // Be aware that the channel layout and count can be different for in and
    // out frames. In some situations the caller will fix up the frames before
    // or after conversion. The sample rates can also be different.
    AVFrame *av_i = in ? mp_aframe_get_raw_avframe(in) : NULL;
    AVFrame *av_o = out ? mp_aframe_get_raw_avframe(out) : NULL;
    return avresample_convert(r,
        av_o ? av_o->extended_data : NULL,
        av_o ? av_o->linesize[0] : 0,
        av_o ? av_o->nb_samples : 0,
        av_i ? av_i->extended_data : NULL,
        av_i ? av_i->linesize[0] : 0,
        av_i ? MPMIN(av_i->nb_samples, consume_in) : 0);
}