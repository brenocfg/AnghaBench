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
struct priv {scalar_t__ context; int /*<<< orphan*/  hdc; } ;
typedef  scalar_t__ HGLRC ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  MP_FATAL (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wglCreateContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wglDeleteContext (scalar_t__) ; 
 int /*<<< orphan*/  wglMakeCurrent (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool create_context_wgl_old(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;

    HDC windc = p->hdc;
    bool res = false;

    HGLRC context = wglCreateContext(windc);
    if (!context) {
        MP_FATAL(ctx->vo, "Could not create GL context!\n");
        return res;
    }

    if (!wglMakeCurrent(windc, context)) {
        MP_FATAL(ctx->vo, "Could not set GL context!\n");
        wglDeleteContext(context);
        return res;
    }

    p->context = context;
    return true;
}