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
struct vo_wayland_state {int scaling; TYPE_2__* vo; int /*<<< orphan*/  surface; int /*<<< orphan*/  geometry; } ;
struct ra_ctx {TYPE_1__* vo; struct priv* priv; } ;
struct priv {scalar_t__ egl_window; } ;
typedef  int int32_t ;
struct TYPE_4__ {int dwidth; int dheight; } ;
struct TYPE_3__ {struct vo_wayland_state* wl; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (struct vo_wayland_state*,char*) ; 
 int mp_rect_h (int /*<<< orphan*/ ) ; 
 int mp_rect_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_egl_window_resize (scalar_t__,int const,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_surface_set_buffer_scale (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void resize(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;
    struct vo_wayland_state *wl = ctx->vo->wl;

    MP_VERBOSE(wl, "Handling resize on the egl side\n");

    const int32_t width = wl->scaling*mp_rect_w(wl->geometry);
    const int32_t height = wl->scaling*mp_rect_h(wl->geometry);

    wl_surface_set_buffer_scale(wl->surface, wl->scaling);

    if (p->egl_window)
        wl_egl_window_resize(p->egl_window, width, height, 0, 0);

    wl->vo->dwidth  = width;
    wl->vo->dheight = height;
}