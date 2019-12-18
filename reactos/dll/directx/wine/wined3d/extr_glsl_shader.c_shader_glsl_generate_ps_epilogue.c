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
struct wined3d_string_buffer {int dummy; } ;
struct TYPE_2__ {int major; } ;
struct wined3d_shader_reg_maps {TYPE_1__ shader_version; } ;
struct wined3d_shader {struct wined3d_shader_reg_maps reg_maps; } ;
struct wined3d_gl_info {int dummy; } ;
struct ps_compile_args {scalar_t__ alpha_test_func; int /*<<< orphan*/  fog; scalar_t__ srgb_correction; } ;

/* Variables and functions */
 scalar_t__ needs_legacy_glsl_syntax (struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,char const*) ; 
 int /*<<< orphan*/  shader_glsl_generate_alpha_test (struct wined3d_string_buffer*,struct wined3d_gl_info const*,scalar_t__) ; 
 int /*<<< orphan*/  shader_glsl_generate_fog_code (struct wined3d_string_buffer*,struct wined3d_gl_info const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_generate_srgb_write_correction (struct wined3d_string_buffer*,struct wined3d_gl_info const*) ; 

__attribute__((used)) static void shader_glsl_generate_ps_epilogue(const struct wined3d_gl_info *gl_info,
        struct wined3d_string_buffer *buffer, const struct wined3d_shader *shader,
        const struct ps_compile_args *args)
{
    const struct wined3d_shader_reg_maps *reg_maps = &shader->reg_maps;
    const char *output = needs_legacy_glsl_syntax(gl_info) ? "gl_FragData[0]" : "ps_out0";

    /* Pixel shaders < 2.0 place the resulting color in R0 implicitly. */
    if (reg_maps->shader_version.major < 2)
        shader_addline(buffer, "%s = R0;\n", output);

    if (args->srgb_correction)
        shader_glsl_generate_srgb_write_correction(buffer, gl_info);

    /* SM < 3 does not replace the fog stage. */
    if (reg_maps->shader_version.major < 3)
        shader_glsl_generate_fog_code(buffer, gl_info, args->fog);

    shader_glsl_generate_alpha_test(buffer, gl_info, args->alpha_test_func + 1);
}