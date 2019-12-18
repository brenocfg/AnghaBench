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
struct mp_aframe {double pts; TYPE_1__* av_frame; } ;
struct TYPE_2__ {void* nb_samples; } ;

/* Variables and functions */
 void* MPCLAMP (int,int /*<<< orphan*/ ,void*) ; 
 double MP_NOPTS_VALUE ; 
 scalar_t__ af_fmt_is_spdif (int /*<<< orphan*/ ) ; 
 double mp_aframe_end_pts (struct mp_aframe*) ; 
 double mp_aframe_get_effective_rate (struct mp_aframe*) ; 
 int /*<<< orphan*/  mp_aframe_get_format (struct mp_aframe*) ; 
 int /*<<< orphan*/  mp_aframe_skip_samples (struct mp_aframe*,int) ; 

void mp_aframe_clip_timestamps(struct mp_aframe *f, double start, double end)
{
    double f_end = mp_aframe_end_pts(f);
    double rate = mp_aframe_get_effective_rate(f);
    if (f_end == MP_NOPTS_VALUE)
        return;
    if (af_fmt_is_spdif(mp_aframe_get_format(f)))
        return;
    if (end != MP_NOPTS_VALUE) {
        if (f_end >= end) {
            if (f->pts >= end) {
                f->av_frame->nb_samples = 0;
            } else {
                int new = (end - f->pts) * rate;
                f->av_frame->nb_samples = MPCLAMP(new, 0, f->av_frame->nb_samples);
            }
        }
    }
    if (start != MP_NOPTS_VALUE) {
        if (f->pts < start) {
            if (f_end <= start) {
                f->av_frame->nb_samples = 0;
                f->pts = f_end;
            } else {
                int skip = (start - f->pts) * rate;
                skip = MPCLAMP(skip, 0, f->av_frame->nb_samples);
                mp_aframe_skip_samples(f, skip);
            }
        }
    }
}