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
struct wined3d_string_buffer {char* buffer; } ;
struct wined3d_gl_info {int dummy; } ;
struct shader_glsl_priv {int /*<<< orphan*/  string_buffers; } ;
struct glsl_ps_program {void* color_key_location; void* ycorrection_location; void* np2_fixup_location; void* alpha_test_ref_location; void* fog_scale_location; void* fog_end_location; void* fog_density_location; void* fog_color_location; void* specular_enable_location; void* tex_factor_location; void** tss_constant_location; void** bumpenv_lum_offset_location; void** bumpenv_lum_scale_location; void** bumpenv_mat_location; void** uniform_b_locations; void** uniform_i_locations; void** uniform_f_locations; } ;
typedef  int /*<<< orphan*/  GLuint ;

/* Variables and functions */
 void* GL_EXTCALL (int /*<<< orphan*/ ) ; 
 unsigned int MAX_TEXTURES ; 
 unsigned int WINED3D_MAX_CONSTS_B ; 
 unsigned int WINED3D_MAX_CONSTS_I ; 
 unsigned int WINED3D_MAX_PS_CONSTS_F ; 
 int /*<<< orphan*/  glGetUniformLocation (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (void**,int,unsigned int) ; 
 struct wined3d_string_buffer* string_buffer_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_buffer_release (int /*<<< orphan*/ *,struct wined3d_string_buffer*) ; 
 int /*<<< orphan*/  string_buffer_sprintf (struct wined3d_string_buffer*,char*,unsigned int) ; 

__attribute__((used)) static void shader_glsl_init_ps_uniform_locations(const struct wined3d_gl_info *gl_info,
        struct shader_glsl_priv *priv, GLuint program_id, struct glsl_ps_program *ps, unsigned int ps_c_count)
{
    unsigned int i;
    struct wined3d_string_buffer *name = string_buffer_get(&priv->string_buffers);

    for (i = 0; i < ps_c_count; ++i)
    {
        string_buffer_sprintf(name, "ps_c[%u]", i);
        ps->uniform_f_locations[i] = GL_EXTCALL(glGetUniformLocation(program_id, name->buffer));
    }
    memset(&ps->uniform_f_locations[ps_c_count], 0xff, (WINED3D_MAX_PS_CONSTS_F - ps_c_count) * sizeof(GLuint));

    for (i = 0; i < WINED3D_MAX_CONSTS_I; ++i)
    {
        string_buffer_sprintf(name, "ps_i[%u]", i);
        ps->uniform_i_locations[i] = GL_EXTCALL(glGetUniformLocation(program_id, name->buffer));
    }

    for (i = 0; i < WINED3D_MAX_CONSTS_B; ++i)
    {
        string_buffer_sprintf(name, "ps_b[%u]", i);
        ps->uniform_b_locations[i] = GL_EXTCALL(glGetUniformLocation(program_id, name->buffer));
    }

    for (i = 0; i < MAX_TEXTURES; ++i)
    {
        string_buffer_sprintf(name, "bumpenv_mat%u", i);
        ps->bumpenv_mat_location[i] = GL_EXTCALL(glGetUniformLocation(program_id, name->buffer));
        string_buffer_sprintf(name, "bumpenv_lum_scale%u", i);
        ps->bumpenv_lum_scale_location[i] = GL_EXTCALL(glGetUniformLocation(program_id, name->buffer));
        string_buffer_sprintf(name, "bumpenv_lum_offset%u", i);
        ps->bumpenv_lum_offset_location[i] = GL_EXTCALL(glGetUniformLocation(program_id, name->buffer));
        string_buffer_sprintf(name, "tss_const%u", i);
        ps->tss_constant_location[i] = GL_EXTCALL(glGetUniformLocation(program_id, name->buffer));
    }

    ps->tex_factor_location = GL_EXTCALL(glGetUniformLocation(program_id, "tex_factor"));
    ps->specular_enable_location = GL_EXTCALL(glGetUniformLocation(program_id, "specular_enable"));

    ps->fog_color_location = GL_EXTCALL(glGetUniformLocation(program_id, "ffp_fog.color"));
    ps->fog_density_location = GL_EXTCALL(glGetUniformLocation(program_id, "ffp_fog.density"));
    ps->fog_end_location = GL_EXTCALL(glGetUniformLocation(program_id, "ffp_fog.end"));
    ps->fog_scale_location = GL_EXTCALL(glGetUniformLocation(program_id, "ffp_fog.scale"));

    ps->alpha_test_ref_location = GL_EXTCALL(glGetUniformLocation(program_id, "alpha_test_ref"));

    ps->np2_fixup_location = GL_EXTCALL(glGetUniformLocation(program_id, "ps_samplerNP2Fixup"));
    ps->ycorrection_location = GL_EXTCALL(glGetUniformLocation(program_id, "ycorrection"));
    ps->color_key_location = GL_EXTCALL(glGetUniformLocation(program_id, "color_key"));

    string_buffer_release(&priv->string_buffers, name);
}