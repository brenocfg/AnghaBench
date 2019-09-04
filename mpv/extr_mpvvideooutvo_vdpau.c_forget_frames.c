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
struct vo {struct vdpctx* priv; } ;
struct vdpctx {int dropped_frame; int /*<<< orphan*/  current_image; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_image_unrefp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void forget_frames(struct vo *vo, bool seek_reset)
{
    struct vdpctx *vc = vo->priv;

    if (!seek_reset)
        mp_image_unrefp(&vc->current_image);

    vc->dropped_frame = false;
}