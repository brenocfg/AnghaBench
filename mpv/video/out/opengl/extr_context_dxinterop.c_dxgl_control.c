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
struct ra_ctx {int /*<<< orphan*/  vo; } ;

/* Variables and functions */
 int VO_EVENT_RESIZE ; 
 int /*<<< orphan*/  resize (struct ra_ctx*) ; 
 int vo_w32_control (int /*<<< orphan*/ ,int*,int,void*) ; 

__attribute__((used)) static int dxgl_control(struct ra_ctx *ctx, int *events, int request,
                             void *arg)
{
    int ret = vo_w32_control(ctx->vo, events, request, arg);
    if (*events & VO_EVENT_RESIZE)
        resize(ctx);
    return ret;
}