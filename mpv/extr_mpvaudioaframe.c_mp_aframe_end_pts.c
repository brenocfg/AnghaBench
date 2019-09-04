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
struct TYPE_2__ {double nb_samples; } ;

/* Variables and functions */
 scalar_t__ MP_NOPTS_VALUE ; 
 double mp_aframe_get_effective_rate (struct mp_aframe*) ; 

double mp_aframe_end_pts(struct mp_aframe *f)
{
    double rate = mp_aframe_get_effective_rate(f);
    if (f->pts == MP_NOPTS_VALUE || rate <= 0)
        return MP_NOPTS_VALUE;
    return f->pts + f->av_frame->nb_samples / rate;
}