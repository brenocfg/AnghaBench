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
struct wined3d_state {int dummy; } ;
struct wined3d_context {unsigned int shader_update_mask; TYPE_2__* gl_info; } ;
struct TYPE_3__ {scalar_t__ glsl_varyings; } ;
struct TYPE_4__ {TYPE_1__ limits; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 unsigned int WINED3D_SHADER_TYPE_PIXEL ; 
 scalar_t__ wined3d_max_compat_varyings (TYPE_2__*) ; 

__attribute__((used)) static void glsl_fragment_pipe_vs(struct wined3d_context *context,
        const struct wined3d_state *state, DWORD state_id)
{
    /* Because of settings->texcoords_initialized and args->texcoords_initialized. */
    if (context->gl_info->limits.glsl_varyings < wined3d_max_compat_varyings(context->gl_info))
        context->shader_update_mask |= 1u << WINED3D_SHADER_TYPE_PIXEL;
}