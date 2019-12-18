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
struct mp_rect {int x1; int x0; int y1; int y0; } ;
struct xvctx {int /*<<< orphan*/  vo_gc; int /*<<< orphan*/  xv_port; scalar_t__ Shmem_Flag; struct mp_rect dst_rect; struct mp_rect src_rect; } ;
struct vo_x11_state {int /*<<< orphan*/  window; int /*<<< orphan*/  display; int /*<<< orphan*/  ShmCompletionWaitCount; } ;
struct vo {struct vo_x11_state* x11; struct xvctx* priv; } ;
typedef  int /*<<< orphan*/  XvImage ;

/* Variables and functions */
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  XvPutImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  XvShmPutImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int,int,int,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void put_xvimage(struct vo *vo, XvImage *xvi)
{
    struct xvctx *ctx = vo->priv;
    struct vo_x11_state *x11 = vo->x11;
    struct mp_rect *src = &ctx->src_rect;
    struct mp_rect *dst = &ctx->dst_rect;
    int dw = dst->x1 - dst->x0, dh = dst->y1 - dst->y0;
    int sw = src->x1 - src->x0, sh = src->y1 - src->y0;

    if (ctx->Shmem_Flag) {
        XvShmPutImage(x11->display, ctx->xv_port, x11->window, ctx->vo_gc, xvi,
                      src->x0, src->y0, sw, sh,
                      dst->x0, dst->y0, dw, dh,
                      True);
        x11->ShmCompletionWaitCount++;
    } else {
        XvPutImage(x11->display, ctx->xv_port, x11->window, ctx->vo_gc, xvi,
                   src->x0, src->y0, sw, sh,
                   dst->x0, dst->y0, dw, dh);
    }
}