#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wined3d_state {TYPE_3__** shader; } ;
struct wined3d_context {unsigned int shader_update_mask; struct glsl_context_data* shader_backend_data; } ;
struct glsl_context_data {scalar_t__ rasterization_disabled; } ;
struct TYPE_4__ {int major; } ;
struct TYPE_5__ {TYPE_1__ shader_version; } ;
struct TYPE_6__ {TYPE_2__ reg_maps; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 size_t WINED3D_SHADER_TYPE_DOMAIN ; 
 size_t WINED3D_SHADER_TYPE_GEOMETRY ; 
 unsigned int WINED3D_SHADER_TYPE_PIXEL ; 
 size_t WINED3D_SHADER_TYPE_VERTEX ; 
 scalar_t__ is_rasterization_disabled (TYPE_3__*) ; 

__attribute__((used)) static void glsl_vertex_pipe_geometry_shader(struct wined3d_context *context,
        const struct wined3d_state *state, DWORD state_id)
{
    struct glsl_context_data *ctx_data = context->shader_backend_data;
    BOOL rasterization_disabled;

    rasterization_disabled = is_rasterization_disabled(state->shader[WINED3D_SHADER_TYPE_GEOMETRY]);
    if (ctx_data->rasterization_disabled != rasterization_disabled)
        context->shader_update_mask |= 1u << WINED3D_SHADER_TYPE_PIXEL;
    ctx_data->rasterization_disabled = rasterization_disabled;

    if (state->shader[WINED3D_SHADER_TYPE_DOMAIN])
        context->shader_update_mask |= 1u << WINED3D_SHADER_TYPE_DOMAIN;
    else if (state->shader[WINED3D_SHADER_TYPE_VERTEX]
            && state->shader[WINED3D_SHADER_TYPE_VERTEX]->reg_maps.shader_version.major >= 4)
        context->shader_update_mask |= 1u << WINED3D_SHADER_TYPE_VERTEX;
}