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
struct ra_hwdec {struct priv* priv; } ;
struct priv {int /*<<< orphan*/ * ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_video_plane (struct ra_hwdec*) ; 
 int /*<<< orphan*/  drm_atomic_destroy_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_current_frame (struct ra_hwdec*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uninit(struct ra_hwdec *hw)
{
    struct priv *p = hw->priv;

    disable_video_plane(hw);
    set_current_frame(hw, NULL);

    if (p->ctx) {
        drm_atomic_destroy_context(p->ctx);
        p->ctx = NULL;
    }
}