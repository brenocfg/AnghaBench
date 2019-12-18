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
struct wined3d_string_buffer {int dummy; } ;
struct wined3d_shader_version {int dummy; } ;
struct wined3d_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,unsigned int) ; 
 unsigned int WINED3D_UNMAPPED_STAGE ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,unsigned int) ; 
 unsigned int shader_glsl_map_tex_unit (struct wined3d_context const*,struct wined3d_shader_version const*,unsigned int) ; 

__attribute__((used)) static void shader_glsl_append_sampler_binding_qualifier(struct wined3d_string_buffer *buffer,
        const struct wined3d_context *context, const struct wined3d_shader_version *shader_version,
        unsigned int sampler_idx)
{
    unsigned int mapped_unit = shader_glsl_map_tex_unit(context, shader_version, sampler_idx);
    if (mapped_unit != WINED3D_UNMAPPED_STAGE)
        shader_addline(buffer, "layout(binding = %u)\n", mapped_unit);
    else
        ERR("Unmapped sampler %u.\n", sampler_idx);
}