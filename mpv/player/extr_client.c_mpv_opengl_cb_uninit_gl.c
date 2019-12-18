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
struct TYPE_5__ {TYPE_1__* client_api; } ;
typedef  TYPE_2__ mpv_opengl_cb_context ;
struct TYPE_4__ {int /*<<< orphan*/ * render_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  mpv_render_context_free (int /*<<< orphan*/ *) ; 

int mpv_opengl_cb_uninit_gl(mpv_opengl_cb_context *ctx)
{
    if (ctx->client_api->render_context)
        mpv_render_context_free(ctx->client_api->render_context);
    ctx->client_api->render_context = NULL;
    return 0;
}