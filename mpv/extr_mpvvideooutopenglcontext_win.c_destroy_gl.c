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
struct ra_ctx {int /*<<< orphan*/  vo; struct priv* priv; } ;
struct priv {int /*<<< orphan*/ * hdc; scalar_t__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * current_wgl_context ; 
 int /*<<< orphan*/  vo_w32_hwnd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wglDeleteContext (scalar_t__) ; 

__attribute__((used)) static void destroy_gl(void *ptr)
{
    struct ra_ctx *ctx = ptr;
    struct priv *p = ctx->priv;
    if (p->context)
        wglDeleteContext(p->context);
    p->context = 0;
    if (p->hdc)
        ReleaseDC(vo_w32_hwnd(ctx->vo), p->hdc);
    p->hdc = NULL;
    current_wgl_context = NULL;
}