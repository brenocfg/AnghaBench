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
struct wined3d_swapchain {int dummy; } ;
struct wined3d_context {int valid; scalar_t__ needs_set; int /*<<< orphan*/  hdc; int /*<<< orphan*/  glCtx; int /*<<< orphan*/  pixel_format; void* hdc_has_format; void* hdc_is_private; scalar_t__ destroyed; struct wined3d_swapchain* swapchain; } ;
typedef  void* BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* FALSE ; 
 int /*<<< orphan*/  FIXME (char*,struct wined3d_context*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 void* TRUE ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int /*<<< orphan*/  context_set_current (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  context_set_pixel_format (struct wined3d_context*) ; 
 int /*<<< orphan*/  swapchain_get_backup_dc (struct wined3d_swapchain*) ; 
 int /*<<< orphan*/  wglMakeCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL context_set_gl_context(struct wined3d_context *ctx)
{
    struct wined3d_swapchain *swapchain = ctx->swapchain;
    BOOL backup = FALSE;

    if (!context_set_pixel_format(ctx))
    {
        WARN("Failed to set pixel format %d on device context %p.\n",
                ctx->pixel_format, ctx->hdc);
        backup = TRUE;
    }

    if (backup || !wglMakeCurrent(ctx->hdc, ctx->glCtx))
    {
        WARN("Failed to make GL context %p current on device context %p, last error %#x.\n",
                ctx->glCtx, ctx->hdc, GetLastError());
        ctx->valid = 0;
        WARN("Trying fallback to the backup window.\n");

        /* FIXME: If the context is destroyed it's no longer associated with
         * a swapchain, so we can't use the swapchain to get a backup dc. To
         * make this work windowless contexts would need to be handled by the
         * device. */
        if (ctx->destroyed || !swapchain)
        {
            FIXME("Unable to get backup dc for destroyed context %p.\n", ctx);
            context_set_current(NULL);
            return FALSE;
        }

        if (!(ctx->hdc = swapchain_get_backup_dc(swapchain)))
        {
            context_set_current(NULL);
            return FALSE;
        }

        ctx->hdc_is_private = TRUE;
        ctx->hdc_has_format = FALSE;

        if (!context_set_pixel_format(ctx))
        {
            ERR("Failed to set pixel format %d on device context %p.\n",
                    ctx->pixel_format, ctx->hdc);
            context_set_current(NULL);
            return FALSE;
        }

        if (!wglMakeCurrent(ctx->hdc, ctx->glCtx))
        {
            ERR("Fallback to backup window (dc %p) failed too, last error %#x.\n",
                    ctx->hdc, GetLastError());
            context_set_current(NULL);
            return FALSE;
        }

        ctx->valid = 1;
    }
    ctx->needs_set = 0;
    return TRUE;
}