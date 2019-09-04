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
struct vo_wayland_state {int scaling; int /*<<< orphan*/  surface; int /*<<< orphan*/  geometry; } ;
struct ra_ctx {TYPE_1__* vo; } ;
typedef  int int32_t ;
struct TYPE_2__ {struct vo_wayland_state* wl; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (struct vo_wayland_state*,char*) ; 
 int mp_rect_h (int /*<<< orphan*/ ) ; 
 int mp_rect_w (int /*<<< orphan*/ ) ; 
 int ra_vk_ctx_resize (struct ra_ctx*,int const,int const) ; 
 int /*<<< orphan*/  wl_surface_set_buffer_scale (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool resize(struct ra_ctx *ctx)
{
    struct vo_wayland_state *wl = ctx->vo->wl;

    MP_VERBOSE(wl, "Handling resize on the vk side\n");

    const int32_t width = wl->scaling*mp_rect_w(wl->geometry);
    const int32_t height = wl->scaling*mp_rect_h(wl->geometry);

    wl_surface_set_buffer_scale(wl->surface, wl->scaling);
    return ra_vk_ctx_resize(ctx, width, height);
}