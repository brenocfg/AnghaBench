#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ra_hwdec {struct priv* priv; } ;
struct TYPE_8__ {int /*<<< orphan*/ * image; int /*<<< orphan*/  fb; } ;
struct TYPE_7__ {int /*<<< orphan*/  fb; int /*<<< orphan*/ * image; } ;
struct TYPE_6__ {int /*<<< orphan*/  fb; int /*<<< orphan*/ * image; } ;
struct priv {TYPE_4__ current_frame; TYPE_3__ last_frame; TYPE_2__ old_frame; TYPE_1__* ctx; int /*<<< orphan*/  log; } ;
struct drm_frame {int /*<<< orphan*/ * image; int /*<<< orphan*/  fb; } ;
struct TYPE_5__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_prime_destroy_framebuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mp_image_setrefp (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void set_current_frame(struct ra_hwdec *hw, struct drm_frame *frame)
{
    struct priv *p = hw->priv;

    // frame will be on screen after next vsync
    // current_frame is currently the displayed frame and will be replaced
    // by frame after next vsync.
    // We used old frame as triple buffering to make sure that the drm framebuffer
    // is not being displayed when we release it.

    if (p->ctx) {
        drm_prime_destroy_framebuffer(p->log, p->ctx->fd, &p->old_frame.fb);
    }

    mp_image_setrefp(&p->old_frame.image, p->last_frame.image);
    p->old_frame.fb = p->last_frame.fb;

    mp_image_setrefp(&p->last_frame.image, p->current_frame.image);
    p->last_frame.fb = p->current_frame.fb;

    if (frame) {
        p->current_frame.fb = frame->fb;
        mp_image_setrefp(&p->current_frame.image, frame->image);
    } else {
        memset(&p->current_frame.fb, 0, sizeof(p->current_frame.fb));
        mp_image_setrefp(&p->current_frame.image, NULL);
    }
}