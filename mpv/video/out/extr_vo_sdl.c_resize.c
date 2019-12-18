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
struct vo {int dwidth; int dheight; int want_redraw; struct priv* priv; } ;
struct priv {int /*<<< orphan*/  renderer; int /*<<< orphan*/  osd_res; int /*<<< orphan*/  dst_rect; int /*<<< orphan*/  src_rect; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_RenderSetLogicalSize (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  vo_get_src_dst_rects (struct vo*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vo_wakeup (struct vo*) ; 

__attribute__((used)) static void resize(struct vo *vo, int w, int h)
{
    struct priv *vc = vo->priv;
    vo->dwidth = w;
    vo->dheight = h;
    vo_get_src_dst_rects(vo, &vc->src_rect, &vc->dst_rect,
                         &vc->osd_res);
    SDL_RenderSetLogicalSize(vc->renderer, w, h);
    vo->want_redraw = true;
    vo_wakeup(vo);
}