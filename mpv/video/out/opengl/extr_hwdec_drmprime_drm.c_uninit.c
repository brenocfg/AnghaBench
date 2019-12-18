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
struct ra_hwdec {int /*<<< orphan*/  devs; struct priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  av_device_ref; } ;
struct priv {int /*<<< orphan*/ * ctx; TYPE_1__ hwctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_video_plane (struct ra_hwdec*) ; 
 int /*<<< orphan*/  drm_atomic_destroy_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hwdec_devices_remove (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  set_current_frame (struct ra_hwdec*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uninit(struct ra_hwdec *hw)
{
    struct priv *p = hw->priv;

    disable_video_plane(hw);
    set_current_frame(hw, NULL);

    hwdec_devices_remove(hw->devs, &p->hwctx);
    av_buffer_unref(&p->hwctx.av_device_ref);

    if (p->ctx) {
        drm_atomic_destroy_context(p->ctx);
        p->ctx = NULL;
    }
}