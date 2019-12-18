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
struct vo {struct priv* priv; } ;
struct priv {int fb_queue_len; int swapchain_depth; TYPE_1__** fb_queue; scalar_t__ waiting_for_flip; int /*<<< orphan*/  active; scalar_t__ still; scalar_t__ paused; } ;
struct TYPE_2__ {int /*<<< orphan*/  fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct vo*,char*) ; 
 int /*<<< orphan*/  queue_flip (struct vo*,TYPE_1__*) ; 
 int /*<<< orphan*/  swapchain_step (struct vo*) ; 
 int /*<<< orphan*/  wait_on_flip (struct vo*) ; 

__attribute__((used)) static void flip_page(struct vo *vo)
{
    struct priv *p = vo->priv;
    const bool drain = p->paused || p->still;

    if (!p->active)
        return;

    while (drain || p->fb_queue_len > p->swapchain_depth) {
        if (p->waiting_for_flip) {
            wait_on_flip(vo);
            swapchain_step(vo);
        }
        if (p->fb_queue_len <= 1)
            break;
        if (!p->fb_queue[1] || !p->fb_queue[1]->fb) {
            MP_ERR(vo, "Hole in swapchain?\n");
            swapchain_step(vo);
            continue;
        }
        queue_flip(vo, p->fb_queue[1]);
    }
}