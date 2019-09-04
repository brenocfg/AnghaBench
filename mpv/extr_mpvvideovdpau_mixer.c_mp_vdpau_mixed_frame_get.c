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
typedef  void mp_vdpau_mixer_frame ;
struct mp_image {scalar_t__ imgfmt; scalar_t__* planes; } ;

/* Variables and functions */
 scalar_t__ IMGFMT_VDPAU ; 

struct mp_vdpau_mixer_frame *mp_vdpau_mixed_frame_get(struct mp_image *mpi)
{
    if (mpi->imgfmt != IMGFMT_VDPAU)
        return NULL;
    return (void *)mpi->planes[2];
}