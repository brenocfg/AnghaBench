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
struct TYPE_5__ {int /*<<< orphan*/  (* p_glBindTexture ) (int const,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {TYPE_2__ gl; } ;
struct wined3d_gl_info {TYPE_3__ gl_ops; } ;
struct wined3d_dummy_textures {int /*<<< orphan*/  tex_2d_ms_array; int /*<<< orphan*/  tex_2d_ms; int /*<<< orphan*/  tex_buffer; int /*<<< orphan*/  tex_3d; int /*<<< orphan*/  tex_cube_array; int /*<<< orphan*/  tex_cube; int /*<<< orphan*/  tex_rect; int /*<<< orphan*/  tex_2d_array; int /*<<< orphan*/  tex_2d; int /*<<< orphan*/  tex_1d_array; int /*<<< orphan*/  tex_1d; } ;
struct wined3d_context {size_t active_texture; size_t* texture_type; struct wined3d_gl_info* gl_info; TYPE_1__* device; } ;
struct TYPE_4__ {struct wined3d_dummy_textures dummy_textures; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  size_t GLenum ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,size_t) ; 
#define  GL_NONE 139 
#define  GL_TEXTURE_1D 138 
#define  GL_TEXTURE_1D_ARRAY 137 
#define  GL_TEXTURE_2D 136 
#define  GL_TEXTURE_2D_ARRAY 135 
#define  GL_TEXTURE_2D_MULTISAMPLE 134 
#define  GL_TEXTURE_2D_MULTISAMPLE_ARRAY 133 
#define  GL_TEXTURE_3D 132 
#define  GL_TEXTURE_BUFFER 131 
#define  GL_TEXTURE_CUBE_MAP 130 
#define  GL_TEXTURE_CUBE_MAP_ARRAY 129 
#define  GL_TEXTURE_RECTANGLE_ARB 128 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  stub1 (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (int const,int /*<<< orphan*/ ) ; 

void context_bind_texture(struct wined3d_context *context, GLenum target, GLuint name)
{
    const struct wined3d_dummy_textures *textures = &context->device->dummy_textures;
    const struct wined3d_gl_info *gl_info = context->gl_info;
    DWORD unit = context->active_texture;
    DWORD old_texture_type = context->texture_type[unit];

    if (name)
    {
        gl_info->gl_ops.gl.p_glBindTexture(target, name);
    }
    else
    {
        target = GL_NONE;
    }

    if (old_texture_type != target)
    {
        switch (old_texture_type)
        {
            case GL_NONE:
                /* nothing to do */
                break;
            case GL_TEXTURE_1D:
                gl_info->gl_ops.gl.p_glBindTexture(GL_TEXTURE_1D, textures->tex_1d);
                checkGLcall("glBindTexture");
                break;
            case GL_TEXTURE_1D_ARRAY:
                gl_info->gl_ops.gl.p_glBindTexture(GL_TEXTURE_1D_ARRAY, textures->tex_1d_array);
                checkGLcall("glBindTexture");
                break;
            case GL_TEXTURE_2D:
                gl_info->gl_ops.gl.p_glBindTexture(GL_TEXTURE_2D, textures->tex_2d);
                break;
            case GL_TEXTURE_2D_ARRAY:
                gl_info->gl_ops.gl.p_glBindTexture(GL_TEXTURE_2D_ARRAY, textures->tex_2d_array);
                break;
            case GL_TEXTURE_RECTANGLE_ARB:
                gl_info->gl_ops.gl.p_glBindTexture(GL_TEXTURE_RECTANGLE_ARB, textures->tex_rect);
                break;
            case GL_TEXTURE_CUBE_MAP:
                gl_info->gl_ops.gl.p_glBindTexture(GL_TEXTURE_CUBE_MAP, textures->tex_cube);
                break;
            case GL_TEXTURE_CUBE_MAP_ARRAY:
                gl_info->gl_ops.gl.p_glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, textures->tex_cube_array);
                break;
            case GL_TEXTURE_3D:
                gl_info->gl_ops.gl.p_glBindTexture(GL_TEXTURE_3D, textures->tex_3d);
                break;
            case GL_TEXTURE_BUFFER:
                gl_info->gl_ops.gl.p_glBindTexture(GL_TEXTURE_BUFFER, textures->tex_buffer);
                break;
            case GL_TEXTURE_2D_MULTISAMPLE:
                gl_info->gl_ops.gl.p_glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, textures->tex_2d_ms);
                break;
            case GL_TEXTURE_2D_MULTISAMPLE_ARRAY:
                gl_info->gl_ops.gl.p_glBindTexture(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, textures->tex_2d_ms_array);
                break;
            default:
                ERR("Unexpected texture target %#x.\n", old_texture_type);
        }

        context->texture_type[unit] = target;
    }

    checkGLcall("bind texture");
}