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
struct vo_frame {int /*<<< orphan*/  current; int /*<<< orphan*/  redraw; int /*<<< orphan*/  repeat; int /*<<< orphan*/  still; } ;
struct vo {struct priv* priv; } ;
struct priv {size_t front_buf; struct framebuffer* bufs; int /*<<< orphan*/  still; int /*<<< orphan*/  active; } ;
struct framebuffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  draw_image (struct vo*,int /*<<< orphan*/ ,struct framebuffer*) ; 
 int /*<<< orphan*/  enqueue_frame (struct vo*,struct framebuffer*) ; 
 struct framebuffer* get_new_fb (struct vo*) ; 
 int /*<<< orphan*/  mp_image_new_ref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void draw_frame(struct vo *vo, struct vo_frame *frame)
{
    struct priv *p = vo->priv;

    if (!p->active)
        return;

    p->still = frame->still;

    // we redraw the entire image when OSD needs to be redrawn
    const bool repeat = frame->repeat && !frame->redraw;

    struct framebuffer *fb =  &p->bufs[p->front_buf];
    if (!repeat) {
        fb = get_new_fb(vo);
        draw_image(vo, mp_image_new_ref(frame->current), fb);
    }

    enqueue_frame(vo, fb);
}