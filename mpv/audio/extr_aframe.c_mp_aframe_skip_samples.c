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
struct mp_aframe {scalar_t__ pts; TYPE_1__* av_frame; } ;
struct TYPE_2__ {int nb_samples; scalar_t__* extended_data; } ;

/* Variables and functions */
 scalar_t__ MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ av_frame_make_writable (TYPE_1__*) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 
 int mp_aframe_get_effective_rate (struct mp_aframe*) ; 
 int mp_aframe_get_planes (struct mp_aframe*) ; 
 int mp_aframe_get_size (struct mp_aframe*) ; 
 size_t mp_aframe_get_sstride (struct mp_aframe*) ; 

void mp_aframe_skip_samples(struct mp_aframe *f, int samples)
{
    assert(samples >= 0 && samples <= mp_aframe_get_size(f));

    if (av_frame_make_writable(f->av_frame) < 0)
        return; // go complain to ffmpeg

    int num_planes = mp_aframe_get_planes(f);
    size_t sstride = mp_aframe_get_sstride(f);
    for (int n = 0; n < num_planes; n++) {
        memmove(f->av_frame->extended_data[n],
                f->av_frame->extended_data[n] + samples * sstride,
                (f->av_frame->nb_samples - samples) * sstride);
    }

    f->av_frame->nb_samples -= samples;

    if (f->pts != MP_NOPTS_VALUE)
        f->pts += samples / mp_aframe_get_effective_rate(f);
}