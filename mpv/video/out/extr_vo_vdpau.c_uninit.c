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
struct vo {int /*<<< orphan*/  hwdec_devs; struct vdpctx* priv; } ;
struct vdpctx {int /*<<< orphan*/  video_mixer; TYPE_1__* mpvdp; } ;
struct TYPE_2__ {int /*<<< orphan*/  hwctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_vdpau_objects (struct vo*) ; 
 int /*<<< orphan*/  hwdec_devices_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwdec_devices_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_vdpau_mixer_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vo_x11_uninit (struct vo*) ; 

__attribute__((used)) static void uninit(struct vo *vo)
{
    struct vdpctx *vc = vo->priv;

    hwdec_devices_remove(vo->hwdec_devs, &vc->mpvdp->hwctx);
    hwdec_devices_destroy(vo->hwdec_devs);

    /* Destroy all vdpau objects */
    mp_vdpau_mixer_destroy(vc->video_mixer);
    destroy_vdpau_objects(vo);

    vo_x11_uninit(vo);
}