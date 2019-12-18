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
struct xvctx {int /*<<< orphan*/  f_gc; } ;
struct vo_x11_state {int /*<<< orphan*/  display; } ;
struct vo {int dwidth; int dheight; struct xvctx* priv; struct vo_x11_state* x11; } ;
struct mp_rect {int y0; int y1; int x0; int /*<<< orphan*/  x1; } ;
typedef  int /*<<< orphan*/  GC ;

/* Variables and functions */
 int /*<<< orphan*/  XFlush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_rect (struct vo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void vo_x11_clear_background(struct vo *vo, const struct mp_rect *rc)
{
    struct vo_x11_state *x11 = vo->x11;
    struct xvctx *ctx = vo->priv;
    GC gc = ctx->f_gc;

    int w = vo->dwidth;
    int h = vo->dheight;

    fill_rect(vo, gc, 0,      0,      w,      rc->y0); // top
    fill_rect(vo, gc, 0,      rc->y1, w,      h);      // bottom
    fill_rect(vo, gc, 0,      rc->y0, rc->x0, rc->y1); // left
    fill_rect(vo, gc, rc->x1, rc->y0, w,      rc->y1); // right

    XFlush(x11->display);
}