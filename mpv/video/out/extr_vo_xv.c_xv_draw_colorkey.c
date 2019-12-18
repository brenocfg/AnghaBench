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
struct TYPE_2__ {scalar_t__ method; } ;
struct xvctx {int /*<<< orphan*/  vo_gc; int /*<<< orphan*/  xv_colorkey; TYPE_1__ xv_ck_info; } ;
struct vo_x11_state {int /*<<< orphan*/  window; int /*<<< orphan*/  display; } ;
struct vo {struct vo_x11_state* x11; struct xvctx* priv; } ;
struct mp_rect {scalar_t__ y0; scalar_t__ y1; scalar_t__ x0; scalar_t__ x1; } ;

/* Variables and functions */
 scalar_t__ CK_METHOD_BACKGROUND ; 
 scalar_t__ CK_METHOD_MANUALFILL ; 
 int /*<<< orphan*/  XFillRectangle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XSetForeground (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xv_draw_colorkey(struct vo *vo, const struct mp_rect *rc)
{
    struct xvctx *ctx = vo->priv;
    struct vo_x11_state *x11 = vo->x11;
    if (ctx->xv_ck_info.method == CK_METHOD_MANUALFILL ||
        ctx->xv_ck_info.method == CK_METHOD_BACKGROUND)
    {
        if (!ctx->vo_gc)
            return;
        //less tearing than XClearWindow()
        XSetForeground(x11->display, ctx->vo_gc, ctx->xv_colorkey);
        XFillRectangle(x11->display, x11->window, ctx->vo_gc, rc->x0, rc->y0,
                       rc->x1 - rc->x0, rc->y1 - rc->y0);
    }
}