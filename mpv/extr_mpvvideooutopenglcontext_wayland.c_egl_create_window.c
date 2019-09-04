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
struct vo_wayland_state {int /*<<< orphan*/  geometry; int /*<<< orphan*/  surface; } ;
struct ra_ctx {TYPE_1__* vo; struct priv* priv; } ;
struct priv {int /*<<< orphan*/  egl_display; int /*<<< orphan*/  egl_context; int /*<<< orphan*/  egl_surface; int /*<<< orphan*/  egl_window; int /*<<< orphan*/  egl_config; } ;
struct TYPE_2__ {struct vo_wayland_state* wl; } ;

/* Variables and functions */
 int /*<<< orphan*/  eglCreateWindowSurface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eglMakeCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglSwapInterval (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_rect_h (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_rect_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_egl_window_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void egl_create_window(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;
    struct vo_wayland_state *wl = ctx->vo->wl;

    p->egl_window = wl_egl_window_create(wl->surface, mp_rect_w(wl->geometry),
                                         mp_rect_h(wl->geometry));

    p->egl_surface = eglCreateWindowSurface(p->egl_display, p->egl_config,
                                            p->egl_window, NULL);

    eglMakeCurrent(p->egl_display, p->egl_surface, p->egl_surface, p->egl_context);

    eglSwapInterval(p->egl_display, 0);
}