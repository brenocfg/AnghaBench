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
struct wined3d_state {scalar_t__* render_states; } ;
struct wined3d_fb_state {TYPE_2__** render_targets; } ;
struct wined3d_context {TYPE_1__* d3d_info; } ;
struct TYPE_4__ {int format_flags; } ;
struct TYPE_3__ {int wined3d_creation_flags; } ;
typedef  int BOOL ;

/* Variables and functions */
 int WINED3DFMT_FLAG_SRGB_WRITE ; 
 size_t WINED3D_RS_SRGBWRITEENABLE ; 
 int WINED3D_SRGB_READ_WRITE_CONTROL ; 

__attribute__((used)) static inline BOOL needs_srgb_write(const struct wined3d_context *context,
        const struct wined3d_state *state, const struct wined3d_fb_state *fb)
{
    return (!(context->d3d_info->wined3d_creation_flags & WINED3D_SRGB_READ_WRITE_CONTROL)
            || state->render_states[WINED3D_RS_SRGBWRITEENABLE])
            && fb->render_targets[0] && fb->render_targets[0]->format_flags & WINED3DFMT_FLAG_SRGB_WRITE;
}