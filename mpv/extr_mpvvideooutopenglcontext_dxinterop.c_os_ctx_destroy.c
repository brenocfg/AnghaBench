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
struct ra_ctx {struct priv* priv; } ;
struct priv {scalar_t__ os_wnd; scalar_t__ os_dc; scalar_t__ os_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyWindow (scalar_t__) ; 
 int /*<<< orphan*/  ReleaseDC (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wglDeleteContext (scalar_t__) ; 
 int /*<<< orphan*/  wglMakeCurrent (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void os_ctx_destroy(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;

    if (p->os_ctx) {
        wglMakeCurrent(p->os_dc, NULL);
        wglDeleteContext(p->os_ctx);
    }
    if (p->os_dc)
        ReleaseDC(p->os_wnd, p->os_dc);
    if (p->os_wnd)
        DestroyWindow(p->os_wnd);
}