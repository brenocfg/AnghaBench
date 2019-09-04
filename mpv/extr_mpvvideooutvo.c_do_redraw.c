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
struct vo_internal {int request_redraw; int dropped_frame; int /*<<< orphan*/  lock; int /*<<< orphan*/  current_frame; } ;
struct vo_frame {int redraw; int repeat; int still; int duration; scalar_t__ current; scalar_t__ pts; int /*<<< orphan*/  member_0; } ;
struct vo {TYPE_1__* driver; int /*<<< orphan*/  config_ok; struct vo_internal* in; } ;
struct TYPE_2__ {int caps; int (* control ) (struct vo*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* flip_page ) (struct vo*) ;int /*<<< orphan*/  (* draw_image ) (struct vo*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* draw_frame ) (struct vo*,struct vo_frame*) ;int /*<<< orphan*/  untimed; } ;

/* Variables and functions */
 int /*<<< orphan*/  VOCTRL_REDRAW_FRAME ; 
 int VO_CAP_NORETAIN ; 
 int /*<<< orphan*/  mp_image_new_ref (scalar_t__) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct vo*,struct vo_frame*) ; 
 int stub2 (struct vo*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (struct vo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct vo*) ; 
 int /*<<< orphan*/  talloc_free (struct vo_frame*) ; 
 struct vo_frame* vo_frame_ref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_redraw(struct vo *vo)
{
    struct vo_internal *in = vo->in;

    if (!vo->config_ok || (vo->driver->caps & VO_CAP_NORETAIN))
        return;

    pthread_mutex_lock(&in->lock);
    in->request_redraw = false;
    bool full_redraw = in->dropped_frame;
    struct vo_frame *frame = NULL;
    if (!vo->driver->untimed)
        frame = vo_frame_ref(in->current_frame);
    if (frame)
        in->dropped_frame = false;
    struct vo_frame dummy = {0};
    if (!frame)
        frame = &dummy;
    frame->redraw = !full_redraw; // unconditionally redraw if it was dropped
    frame->repeat = false;
    frame->still = true;
    frame->pts = 0;
    frame->duration = -1;
    pthread_mutex_unlock(&in->lock);

    if (vo->driver->draw_frame) {
        vo->driver->draw_frame(vo, frame);
    } else if ((full_redraw || vo->driver->control(vo, VOCTRL_REDRAW_FRAME, NULL) < 1)
               && frame->current)
    {
        vo->driver->draw_image(vo, mp_image_new_ref(frame->current));
    }

    vo->driver->flip_page(vo);

    if (frame != &dummy)
        talloc_free(frame);
}