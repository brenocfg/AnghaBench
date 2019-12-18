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
struct xvctx {int /*<<< orphan*/  src_rect; int /*<<< orphan*/  dst_rect; } ;
struct vo {int want_redraw; int /*<<< orphan*/  input_ctx; struct xvctx* priv; } ;
struct mp_osd_res {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_input_set_mouse_transform (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_xv_csp (struct vo*) ; 
 int /*<<< orphan*/  vo_get_src_dst_rects (struct vo*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct mp_osd_res*) ; 
 int /*<<< orphan*/  vo_x11_clear_background (struct vo*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xv_draw_colorkey (struct vo*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void resize(struct vo *vo)
{
    struct xvctx *ctx = vo->priv;

    // Can't be used, because the function calculates screen-space coordinates,
    // while we need video-space.
    struct mp_osd_res unused;

    vo_get_src_dst_rects(vo, &ctx->src_rect, &ctx->dst_rect, &unused);

    vo_x11_clear_background(vo, &ctx->dst_rect);
    xv_draw_colorkey(vo, &ctx->dst_rect);
    read_xv_csp(vo);

    mp_input_set_mouse_transform(vo->input_ctx, &ctx->dst_rect, &ctx->src_rect);

    vo->want_redraw = true;
}