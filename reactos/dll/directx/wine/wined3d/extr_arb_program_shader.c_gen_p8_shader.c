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
struct wined3d_string_buffer {int /*<<< orphan*/  buffer; } ;
struct wined3d_gl_info {int dummy; } ;
struct arbfp_blit_type {scalar_t__ use_color_key; int /*<<< orphan*/  res_type; } ;
typedef  int /*<<< orphan*/  GLuint ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_FRAGMENT_PROGRAM_ARB ; 
 char* arbfp_texture_target (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindProgramARB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGenProgramsARB (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 
 int /*<<< orphan*/  shader_arb_compile (struct wined3d_gl_info const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_buffer_free (struct wined3d_string_buffer*) ; 
 int /*<<< orphan*/  string_buffer_init (struct wined3d_string_buffer*) ; 

__attribute__((used)) static GLuint gen_p8_shader(const struct wined3d_gl_info *gl_info, const struct arbfp_blit_type *type)
{
    GLuint shader;
    struct wined3d_string_buffer buffer;
    const char *tex_target = arbfp_texture_target(type->res_type);

    /* This should not happen because we only use this conversion for
     * present blits which don't use color keying. */
    if (type->use_color_key)
        FIXME("Implement P8 color keying.\n");

    /* Shader header */
    if (!string_buffer_init(&buffer))
    {
        ERR("Failed to initialize shader buffer.\n");
        return 0;
    }

    GL_EXTCALL(glGenProgramsARB(1, &shader));
    GL_EXTCALL(glBindProgramARB(GL_FRAGMENT_PROGRAM_ARB, shader));
    if (!shader)
    {
        string_buffer_free(&buffer);
        return 0;
    }

    shader_addline(&buffer, "!!ARBfp1.0\n");
    shader_addline(&buffer, "TEMP index;\n");

    /* { 255/256, 0.5/255*255/256, 0, 0 } */
    shader_addline(&buffer, "PARAM constants = { 0.996, 0.00195, 0, 0 };\n");

    /* The alpha-component contains the palette index */
    shader_addline(&buffer, "TEX index, fragment.texcoord[0], texture[0], %s;\n", tex_target);

    /* Scale the index by 255/256 and add a bias of '0.5' in order to sample in the middle */
    shader_addline(&buffer, "MAD index.a, index.a, constants.x, constants.y;\n");

    /* Use the alpha-component as an index in the palette to get the final color */
    shader_addline(&buffer, "TEX result.color, index.a, texture[1], 1D;\n");
    shader_addline(&buffer, "END\n");

    shader_arb_compile(gl_info, GL_FRAGMENT_PROGRAM_ARB, buffer.buffer);

    string_buffer_free(&buffer);

    return shader;
}