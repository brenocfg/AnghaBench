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
struct wined3d_shader {int dummy; } ;
struct wined3d_gl_info {int /*<<< orphan*/ * supported; } ;
struct ds_compile_args {scalar_t__ next_shader_type; } ;

/* Variables and functions */
 size_t ARB_CLIP_CONTROL ; 
 scalar_t__ WINED3D_SHADER_TYPE_PIXEL ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*) ; 
 int /*<<< orphan*/  shader_glsl_fixup_position (struct wined3d_string_buffer*) ; 

__attribute__((used)) static void shader_glsl_generate_ds_epilogue(const struct wined3d_gl_info *gl_info,
        struct wined3d_string_buffer *buffer, const struct wined3d_shader *shader,
        const struct ds_compile_args *args)
{
    shader_addline(buffer, "setup_ds_output(ds_out);\n");

    if (args->next_shader_type == WINED3D_SHADER_TYPE_PIXEL && !gl_info->supported[ARB_CLIP_CONTROL])
        shader_glsl_fixup_position(buffer);
}