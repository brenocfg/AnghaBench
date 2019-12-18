#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  (* p_glBindTexture ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {TYPE_3__ gl; } ;
struct TYPE_6__ {unsigned int combined_samplers; } ;
struct wined3d_gl_info {TYPE_4__ gl_ops; scalar_t__* supported; TYPE_2__ limits; } ;
struct wined3d_dummy_textures {int /*<<< orphan*/  tex_2d_ms_array; int /*<<< orphan*/  tex_2d_ms; int /*<<< orphan*/  tex_buffer; int /*<<< orphan*/  tex_2d_array; int /*<<< orphan*/  tex_1d_array; int /*<<< orphan*/  tex_cube_array; int /*<<< orphan*/  tex_cube; int /*<<< orphan*/  tex_3d; int /*<<< orphan*/  tex_rect; int /*<<< orphan*/  tex_2d; int /*<<< orphan*/  tex_1d; } ;
struct wined3d_device {int dummy; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; TYPE_1__* device; } ;
struct TYPE_5__ {struct wined3d_dummy_textures dummy_textures; } ;

/* Variables and functions */
 size_t ARB_TEXTURE_BUFFER_OBJECT ; 
 size_t ARB_TEXTURE_CUBE_MAP ; 
 size_t ARB_TEXTURE_CUBE_MAP_ARRAY ; 
 size_t ARB_TEXTURE_MULTISAMPLE ; 
 size_t ARB_TEXTURE_RECTANGLE ; 
 size_t EXT_TEXTURE3D ; 
 size_t EXT_TEXTURE_ARRAY ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 scalar_t__ GL_TEXTURE0 ; 
 int /*<<< orphan*/  GL_TEXTURE_1D ; 
 int /*<<< orphan*/  GL_TEXTURE_1D_ARRAY ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_2D_ARRAY ; 
 int /*<<< orphan*/  GL_TEXTURE_2D_MULTISAMPLE ; 
 int /*<<< orphan*/  GL_TEXTURE_2D_MULTISAMPLE_ARRAY ; 
 int /*<<< orphan*/  GL_TEXTURE_3D ; 
 int /*<<< orphan*/  GL_TEXTURE_BUFFER ; 
 int /*<<< orphan*/  GL_TEXTURE_CUBE_MAP ; 
 int /*<<< orphan*/  GL_TEXTURE_CUBE_MAP_ARRAY ; 
 int /*<<< orphan*/  GL_TEXTURE_RECTANGLE_ARB ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  glActiveTexture (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void context_bind_dummy_textures(const struct wined3d_device *device, const struct wined3d_context *context)
{
    const struct wined3d_dummy_textures *textures = &context->device->dummy_textures;
    const struct wined3d_gl_info *gl_info = context->gl_info;
    unsigned int i;

    for (i = 0; i < gl_info->limits.combined_samplers; ++i)
    {
        GL_EXTCALL(glActiveTexture(GL_TEXTURE0 + i));

        gl_info->gl_ops.gl.p_glBindTexture(GL_TEXTURE_1D, textures->tex_1d);
        gl_info->gl_ops.gl.p_glBindTexture(GL_TEXTURE_2D, textures->tex_2d);

        if (gl_info->supported[ARB_TEXTURE_RECTANGLE])
            gl_info->gl_ops.gl.p_glBindTexture(GL_TEXTURE_RECTANGLE_ARB, textures->tex_rect);

        if (gl_info->supported[EXT_TEXTURE3D])
            gl_info->gl_ops.gl.p_glBindTexture(GL_TEXTURE_3D, textures->tex_3d);

        if (gl_info->supported[ARB_TEXTURE_CUBE_MAP])
            gl_info->gl_ops.gl.p_glBindTexture(GL_TEXTURE_CUBE_MAP, textures->tex_cube);

        if (gl_info->supported[ARB_TEXTURE_CUBE_MAP_ARRAY])
            gl_info->gl_ops.gl.p_glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, textures->tex_cube_array);

        if (gl_info->supported[EXT_TEXTURE_ARRAY])
        {
            gl_info->gl_ops.gl.p_glBindTexture(GL_TEXTURE_1D_ARRAY, textures->tex_1d_array);
            gl_info->gl_ops.gl.p_glBindTexture(GL_TEXTURE_2D_ARRAY, textures->tex_2d_array);
        }
        if (gl_info->supported[ARB_TEXTURE_BUFFER_OBJECT])
            gl_info->gl_ops.gl.p_glBindTexture(GL_TEXTURE_BUFFER, textures->tex_buffer);

        if (gl_info->supported[ARB_TEXTURE_MULTISAMPLE])
        {
            gl_info->gl_ops.gl.p_glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, textures->tex_2d_ms);
            gl_info->gl_ops.gl.p_glBindTexture(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, textures->tex_2d_ms_array);
        }
    }

    checkGLcall("bind dummy textures");
}