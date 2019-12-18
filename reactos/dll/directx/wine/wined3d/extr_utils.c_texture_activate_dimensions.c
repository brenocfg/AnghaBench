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
struct wined3d_texture {int target; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* p_glDisable ) (int const) ;int /*<<< orphan*/  (* p_glEnable ) (int const) ;} ;
struct TYPE_4__ {TYPE_1__ gl; } ;
struct wined3d_gl_info {TYPE_2__ gl_ops; scalar_t__* supported; } ;

/* Variables and functions */
 size_t ARB_TEXTURE_CUBE_MAP ; 
 size_t ARB_TEXTURE_RECTANGLE ; 
#define  GL_TEXTURE_1D 132 
#define  GL_TEXTURE_2D 131 
#define  GL_TEXTURE_3D 130 
#define  GL_TEXTURE_CUBE_MAP_ARB 129 
#define  GL_TEXTURE_RECTANGLE_ARB 128 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  stub10 (int const) ; 
 int /*<<< orphan*/  stub11 (int const) ; 
 int /*<<< orphan*/  stub12 (int const) ; 
 int /*<<< orphan*/  stub13 (int) ; 
 int /*<<< orphan*/  stub14 (int) ; 
 int /*<<< orphan*/  stub15 (int const) ; 
 int /*<<< orphan*/  stub16 (int) ; 
 int /*<<< orphan*/  stub17 (int const) ; 
 int /*<<< orphan*/  stub18 (int const) ; 
 int /*<<< orphan*/  stub19 (int const) ; 
 int /*<<< orphan*/  stub2 (int) ; 
 int /*<<< orphan*/  stub20 (int const) ; 
 int /*<<< orphan*/  stub21 (int const) ; 
 int /*<<< orphan*/  stub22 (int const) ; 
 int /*<<< orphan*/  stub23 (int const) ; 
 int /*<<< orphan*/  stub24 (int const) ; 
 int /*<<< orphan*/  stub25 (int const) ; 
 int /*<<< orphan*/  stub26 (int const) ; 
 int /*<<< orphan*/  stub27 (int const) ; 
 int /*<<< orphan*/  stub28 (int const) ; 
 int /*<<< orphan*/  stub29 (int const) ; 
 int /*<<< orphan*/  stub3 (int) ; 
 int /*<<< orphan*/  stub30 (int const) ; 
 int /*<<< orphan*/  stub4 (int) ; 
 int /*<<< orphan*/  stub5 (int const) ; 
 int /*<<< orphan*/  stub6 (int const) ; 
 int /*<<< orphan*/  stub7 (int) ; 
 int /*<<< orphan*/  stub8 (int) ; 
 int /*<<< orphan*/  stub9 (int) ; 

void texture_activate_dimensions(const struct wined3d_texture *texture, const struct wined3d_gl_info *gl_info)
{
    if (texture)
    {
        switch (texture->target)
        {
            case GL_TEXTURE_1D:
                gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_2D);
                checkGLcall("glDisable(GL_TEXTURE_2D)");
                gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_3D);
                checkGLcall("glDisable(GL_TEXTURE_3D)");
                if (gl_info->supported[ARB_TEXTURE_CUBE_MAP])
                {
                    gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_CUBE_MAP_ARB);
                    checkGLcall("glDisable(GL_TEXTURE_CUBE_MAP_ARB)");
                }
                if (gl_info->supported[ARB_TEXTURE_RECTANGLE])
                {
                    gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_RECTANGLE_ARB);
                    checkGLcall("glDisable(GL_TEXTURE_RECTANGLE_ARB)");
                }
                gl_info->gl_ops.gl.p_glEnable(GL_TEXTURE_1D);
                checkGLcall("glEnable(GL_TEXTURE_1D)");
                break;
            case GL_TEXTURE_2D:
                gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_1D);
                checkGLcall("glDisable(GL_TEXTURE_1D)");
                gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_3D);
                checkGLcall("glDisable(GL_TEXTURE_3D)");
                if (gl_info->supported[ARB_TEXTURE_CUBE_MAP])
                {
                    gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_CUBE_MAP_ARB);
                    checkGLcall("glDisable(GL_TEXTURE_CUBE_MAP_ARB)");
                }
                if (gl_info->supported[ARB_TEXTURE_RECTANGLE])
                {
                    gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_RECTANGLE_ARB);
                    checkGLcall("glDisable(GL_TEXTURE_RECTANGLE_ARB)");
                }
                gl_info->gl_ops.gl.p_glEnable(GL_TEXTURE_2D);
                checkGLcall("glEnable(GL_TEXTURE_2D)");
                break;
            case GL_TEXTURE_RECTANGLE_ARB:
                gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_1D);
                checkGLcall("glDisable(GL_TEXTURE_1D)");
                gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_2D);
                checkGLcall("glDisable(GL_TEXTURE_2D)");
                gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_3D);
                checkGLcall("glDisable(GL_TEXTURE_3D)");
                if (gl_info->supported[ARB_TEXTURE_CUBE_MAP])
                {
                    gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_CUBE_MAP_ARB);
                    checkGLcall("glDisable(GL_TEXTURE_CUBE_MAP_ARB)");
                }
                gl_info->gl_ops.gl.p_glEnable(GL_TEXTURE_RECTANGLE_ARB);
                checkGLcall("glEnable(GL_TEXTURE_RECTANGLE_ARB)");
                break;
            case GL_TEXTURE_3D:
                if (gl_info->supported[ARB_TEXTURE_CUBE_MAP])
                {
                    gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_CUBE_MAP_ARB);
                    checkGLcall("glDisable(GL_TEXTURE_CUBE_MAP_ARB)");
                }
                if (gl_info->supported[ARB_TEXTURE_RECTANGLE])
                {
                    gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_RECTANGLE_ARB);
                    checkGLcall("glDisable(GL_TEXTURE_RECTANGLE_ARB)");
                }
                gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_1D);
                checkGLcall("glDisable(GL_TEXTURE_1D)");
                gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_2D);
                checkGLcall("glDisable(GL_TEXTURE_2D)");
                gl_info->gl_ops.gl.p_glEnable(GL_TEXTURE_3D);
                checkGLcall("glEnable(GL_TEXTURE_3D)");
                break;
            case GL_TEXTURE_CUBE_MAP_ARB:
                gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_1D);
                checkGLcall("glDisable(GL_TEXTURE_1D)");
                gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_2D);
                checkGLcall("glDisable(GL_TEXTURE_2D)");
                gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_3D);
                checkGLcall("glDisable(GL_TEXTURE_3D)");
                if (gl_info->supported[ARB_TEXTURE_RECTANGLE])
                {
                    gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_RECTANGLE_ARB);
                    checkGLcall("glDisable(GL_TEXTURE_RECTANGLE_ARB)");
                }
                gl_info->gl_ops.gl.p_glEnable(GL_TEXTURE_CUBE_MAP_ARB);
                checkGLcall("glEnable(GL_TEXTURE_CUBE_MAP_ARB)");
              break;
        }
    }
    else
    {
        gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_1D);
        checkGLcall("glDisable(GL_TEXTURE_1D)");
        gl_info->gl_ops.gl.p_glEnable(GL_TEXTURE_2D);
        checkGLcall("glEnable(GL_TEXTURE_2D)");
        gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_3D);
        checkGLcall("glDisable(GL_TEXTURE_3D)");
        if (gl_info->supported[ARB_TEXTURE_CUBE_MAP])
        {
            gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_CUBE_MAP_ARB);
            checkGLcall("glDisable(GL_TEXTURE_CUBE_MAP_ARB)");
        }
        if (gl_info->supported[ARB_TEXTURE_RECTANGLE])
        {
            gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_RECTANGLE_ARB);
            checkGLcall("glDisable(GL_TEXTURE_RECTANGLE_ARB)");
        }
        /* Binding textures is done by samplers. A dummy texture will be bound */
    }
}