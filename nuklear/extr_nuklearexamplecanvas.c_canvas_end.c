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
struct TYPE_3__ {int /*<<< orphan*/  fixed_background; int /*<<< orphan*/  padding; int /*<<< orphan*/  spacing; } ;
struct TYPE_4__ {TYPE_1__ window; } ;
struct nk_context {TYPE_2__ style; } ;
struct nk_canvas {int /*<<< orphan*/  window_background; int /*<<< orphan*/  item_spacing; int /*<<< orphan*/  panel_padding; } ;

/* Variables and functions */
 int /*<<< orphan*/  nk_end (struct nk_context*) ; 

__attribute__((used)) static void
canvas_end(struct nk_context *ctx, struct nk_canvas *canvas)
{
    nk_end(ctx);
    ctx->style.window.spacing = canvas->panel_padding;
    ctx->style.window.padding = canvas->item_spacing;
    ctx->style.window.fixed_background = canvas->window_background;
}