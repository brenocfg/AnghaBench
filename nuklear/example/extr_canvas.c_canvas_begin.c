#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nk_rect {int /*<<< orphan*/  h; } ;
struct TYPE_3__ {int /*<<< orphan*/  fixed_background; void* padding; void* spacing; } ;
struct TYPE_4__ {TYPE_1__ window; } ;
struct nk_context {TYPE_2__ style; } ;
struct nk_color {int dummy; } ;
struct nk_canvas {int /*<<< orphan*/  painter; int /*<<< orphan*/  window_background; void* item_spacing; void* panel_padding; } ;
typedef  int nk_flags ;

/* Variables and functions */
 int NK_WINDOW_DYNAMIC ; 
 int NK_WINDOW_NO_SCROLLBAR ; 
 int /*<<< orphan*/  nk_begin (struct nk_context*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nk_layout_row_dynamic (struct nk_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nk_rect (int,int,int,int) ; 
 int /*<<< orphan*/  nk_style_item_color (struct nk_color) ; 
 void* nk_vec2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_widget (struct nk_rect*,struct nk_context*) ; 
 int /*<<< orphan*/  nk_window_get_canvas (struct nk_context*) ; 
 struct nk_rect nk_window_get_content_region (struct nk_context*) ; 
 int /*<<< orphan*/  nk_window_set_bounds (struct nk_context*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
canvas_begin(struct nk_context *ctx, struct nk_canvas *canvas, nk_flags flags,
    int x, int y, int width, int height, struct nk_color background_color)
{
    /* save style properties which will be overwritten */
    canvas->panel_padding = ctx->style.window.padding;
    canvas->item_spacing = ctx->style.window.spacing;
    canvas->window_background = ctx->style.window.fixed_background;

    /* use the complete window space and set background */
    ctx->style.window.spacing = nk_vec2(0,0);
    ctx->style.window.padding = nk_vec2(0,0);
    ctx->style.window.fixed_background = nk_style_item_color(background_color);

    /* create/update window and set position + size */
    flags = flags & ~NK_WINDOW_DYNAMIC;
    nk_window_set_bounds(ctx, "Window", nk_rect(x, y, width, height));
    nk_begin(ctx, "Window", nk_rect(x, y, width, height), NK_WINDOW_NO_SCROLLBAR|flags);

    /* allocate the complete window space for drawing */
    {struct nk_rect total_space;
    total_space = nk_window_get_content_region(ctx);
    nk_layout_row_dynamic(ctx, total_space.h, 1);
    nk_widget(&total_space, ctx);
    canvas->painter = nk_window_get_canvas(ctx);}
}