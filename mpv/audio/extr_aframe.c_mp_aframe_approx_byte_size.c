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
struct mp_aframe {TYPE_1__* av_frame; } ;
struct TYPE_2__ {int nb_samples; } ;

/* Variables and functions */
 size_t MPMAX (int,int) ; 
 int MP_ALIGN_UP (size_t,int) ; 
 int mp_aframe_get_planes (struct mp_aframe*) ; 
 size_t mp_aframe_get_sstride (struct mp_aframe*) ; 

int mp_aframe_approx_byte_size(struct mp_aframe *frame)
{
    // God damn, AVFrame is too fucking annoying. Just go with the size that
    // allocating a new frame would use.
    int planes = mp_aframe_get_planes(frame);
    size_t sstride = mp_aframe_get_sstride(frame);
    int samples = frame->av_frame->nb_samples;
    int plane_size = MP_ALIGN_UP(sstride * MPMAX(samples, 1), 32);
    return plane_size * planes + sizeof(*frame);
}