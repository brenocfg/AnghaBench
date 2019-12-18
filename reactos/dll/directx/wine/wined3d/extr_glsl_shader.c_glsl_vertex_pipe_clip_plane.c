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
struct wined3d_state {int dummy; } ;
struct TYPE_2__ {scalar_t__ user_clip_distances; } ;
struct wined3d_gl_info {TYPE_1__ limits; } ;
struct wined3d_context {int /*<<< orphan*/  constant_update_mask; struct wined3d_gl_info* gl_info; } ;
typedef  scalar_t__ UINT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ STATE_CLIPPLANE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINED3D_SHADER_CONST_VS_CLIP_PLANES ; 

__attribute__((used)) static void glsl_vertex_pipe_clip_plane(struct wined3d_context *context,
        const struct wined3d_state *state, DWORD state_id)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;
    UINT index = state_id - STATE_CLIPPLANE(0);

    if (index >= gl_info->limits.user_clip_distances)
        return;

    context->constant_update_mask |= WINED3D_SHADER_CONST_VS_CLIP_PLANES;
}