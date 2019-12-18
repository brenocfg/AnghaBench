#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int mpv_sub_api ;
struct TYPE_6__ {TYPE_1__* mpctx; } ;
typedef  TYPE_2__ mpv_handle ;
struct TYPE_5__ {int /*<<< orphan*/  initialized; } ;

/* Variables and functions */
#define  MPV_SUB_API_OPENGL_CB 128 
 void* opengl_cb_get_context (TYPE_2__*) ; 

void *mpv_get_sub_api(mpv_handle *ctx, mpv_sub_api sub_api)
{
    if (!ctx->mpctx->initialized)
        return NULL;
    void *res = NULL;
    switch (sub_api) {
    case MPV_SUB_API_OPENGL_CB:
        res = opengl_cb_get_context(ctx);
        break;
    default:;
    }
    return res;
}