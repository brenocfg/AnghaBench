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
struct priv {int /*<<< orphan*/  queue; } ;
struct mp_vdpau_mixer_frame {int dummy; } ;
struct mp_image {int /*<<< orphan*/ * planes; } ;
typedef  uintptr_t VdpVideoSurface ;

/* Variables and functions */
 uintptr_t VDP_INVALID_HANDLE ; 
 struct mp_image* mp_image_new_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_refqueue_get_field (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  talloc_steal (struct mp_vdpau_mixer_frame*,struct mp_image*) ; 

__attribute__((used)) static VdpVideoSurface ref_field(struct priv *p,
                                 struct mp_vdpau_mixer_frame *frame, int pos)
{
    struct mp_image *mpi = mp_image_new_ref(mp_refqueue_get_field(p->queue, pos));
    if (!mpi)
        return VDP_INVALID_HANDLE;
    talloc_steal(frame, mpi);
    return (uintptr_t)mpi->planes[3];
}