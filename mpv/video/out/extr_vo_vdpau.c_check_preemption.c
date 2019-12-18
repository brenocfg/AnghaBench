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
struct vo {struct vdpctx* priv; } ;
struct vdpctx {TYPE_1__* mpvdp; int /*<<< orphan*/  vdp_device; int /*<<< orphan*/  preemption_counter; } ;
struct TYPE_2__ {int /*<<< orphan*/  vdp_device; } ;

/* Variables and functions */
 scalar_t__ initialize_vdpau_objects (struct vo*) ; 
 int /*<<< orphan*/  mark_vdpau_objects_uninitialized (struct vo*) ; 
 int mp_vdpau_handle_preemption (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool check_preemption(struct vo *vo)
{
    struct vdpctx *vc = vo->priv;

    int r = mp_vdpau_handle_preemption(vc->mpvdp, &vc->preemption_counter);
    if (r < 1) {
        mark_vdpau_objects_uninitialized(vo);
        if (r < 0)
            return false;
        vc->vdp_device = vc->mpvdp->vdp_device;
        if (initialize_vdpau_objects(vo) < 0)
            return false;
    }
    return true;
}