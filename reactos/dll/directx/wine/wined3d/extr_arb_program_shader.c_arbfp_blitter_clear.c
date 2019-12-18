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
struct wined3d_fb_state {int dummy; } ;
struct wined3d_device {int dummy; } ;
struct wined3d_color {int dummy; } ;
struct wined3d_blitter {TYPE_1__* ops; struct wined3d_blitter* next; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* blitter_clear ) (struct wined3d_blitter*,struct wined3d_device*,unsigned int,struct wined3d_fb_state const*,unsigned int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,struct wined3d_color const*,float,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct wined3d_blitter*,struct wined3d_device*,unsigned int,struct wined3d_fb_state const*,unsigned int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,struct wined3d_color const*,float,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void arbfp_blitter_clear(struct wined3d_blitter *blitter, struct wined3d_device *device,
        unsigned int rt_count, const struct wined3d_fb_state *fb, unsigned int rect_count, const RECT *clear_rects,
        const RECT *draw_rect, DWORD flags, const struct wined3d_color *colour, float depth, DWORD stencil)
{
    struct wined3d_blitter *next;

    if ((next = blitter->next))
        next->ops->blitter_clear(next, device, rt_count, fb, rect_count,
                clear_rects, draw_rect, flags, colour, depth, stencil);
}