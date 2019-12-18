#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vo_frame {int dummy; } ;
struct mpv_render_context {TYPE_2__* renderer; int /*<<< orphan*/  lock; int /*<<< orphan*/  cur_frame; } ;
struct TYPE_5__ {TYPE_1__* fns; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* perfdata ) (TYPE_2__*,void*) ;int /*<<< orphan*/  (* screenshot ) (TYPE_2__*,struct vo_frame*,void*) ;} ;

/* Variables and functions */
#define  VOCTRL_PERFORMANCE_DATA 129 
#define  VOCTRL_SCREENSHOT 128 
 int VO_NOTIMPL ; 
 int VO_TRUE ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,struct vo_frame*,void*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  talloc_free (struct vo_frame*) ; 
 struct vo_frame* vo_frame_ref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void run_control_on_render_thread(void *p)
{
    void **args = p;
    struct mpv_render_context *ctx = args[0];
    int request = (intptr_t)args[1];
    void *data = args[2];
    int ret = VO_NOTIMPL;

    switch (request) {
    case VOCTRL_SCREENSHOT: {
        pthread_mutex_lock(&ctx->lock);
        struct vo_frame *frame = vo_frame_ref(ctx->cur_frame);
        pthread_mutex_unlock(&ctx->lock);
        if (frame && ctx->renderer->fns->screenshot)
            ctx->renderer->fns->screenshot(ctx->renderer, frame, data);
        talloc_free(frame);
        break;
    }
    case VOCTRL_PERFORMANCE_DATA: {
        if (ctx->renderer->fns->perfdata) {
            ctx->renderer->fns->perfdata(ctx->renderer, data);
            ret = VO_TRUE;
        }
        break;
    }
    }

    *(int *)args[3] = ret;
}